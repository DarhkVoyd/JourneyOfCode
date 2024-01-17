import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT *, sum(shares) as shares FROM transactions where user_id = ? group by symbol having sum(shares) > 0", session["user_id"])
    cash = db.execute(
        "SELECT cash FROM users where id = ?", session["user_id"])[0]["cash"]
    holdings = 0
    for stock in stocks:
        currentStatus = lookup(stock["symbol"])
        holdings = holdings + (currentStatus["price"] * stock["shares"])
        stock["name"] = currentStatus["name"]
        stock["amount"] = usd(currentStatus["price"] * stock["shares"])
        stock["price"] = usd(currentStatus["price"])

    return render_template("index.html", stocks=stocks, cash=usd(cash), balance=usd(cash + holdings))


@ app.route("/buy", methods=["GET", "POST"])
@ login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        lookupSymbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("Missing Symbol")
        if not shares:
            return apology("Missing Shares")
        if not lookupSymbol:
            return apology("Invalid Symbol")
        if not shares.isdigit():
            return apology("Invalid Shares")

        # Calculate Amount
        share = lookup(request.form.get("symbol"))
        totalPrice = int(request.form.get("shares")) * share["price"]

        # Autheticate User
        currentUser = db.execute("SELECT * from users where id = ?",
                                 session["user_id"])
        # Execute Purchase
        if currentUser[0]["cash"] >= totalPrice:
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) values (?, ?, ?, ?)",
                       session["user_id"], share["symbol"], int(request.form.get("shares")), share["price"])
            db.execute("UPDATE users SET cash = cash - ? where id = ?",
                       totalPrice, session["user_id"])
            return redirect("/")
        else:
            return apology("Insufficient Funds")
    else:
        return render_template("buy.html")


@ app.route("/history")
@ login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT * from transactions where user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@ app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@ app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@ app.route("/quote", methods=["GET", "POST"])
@ login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("missing symbol")
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol")
        name = stock["name"]
        price = usd(stock["price"])
        symbol = stock["symbol"]
        return render_template("quoted.html", name=name, price=price, symbol=symbol)
    else:
        return render_template("quote.html")


@ app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif (not request.form.get("password") or not request.form.get("confirmation") or (request.form.get("password") != request.form.get("confirmation"))):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))
        if len(rows) != 0:
            return apology("Username is not available")

        # Insert user to database
        db.execute("INSERT INTO users (username, hash) values (?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@ app.route("/sell", methods=["GET", "POST"])
@ login_required
def sell():
    """Sell shares of stock"""
    symbols = db.execute(
        "SELECT sum(shares) as shares, symbol from transactions where user_id = ? GROUP BY symbol having sum(shares) > 0", session["user_id"])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure Symbol is selected
        if not symbol:
            return apology("Missing Symbol")

        # Ensure shares are selected and valid
        if not shares or int(shares) <= 0:
            return apology("Missing Shares")

        currentStatus = lookup(symbol)
        availableShares = db.execute(
            "SELECT sum(shares) as shares from transactions where user_id = ? and symbol = ? GROUP BY symbol", session["user_id"], symbol)[0]["shares"]
        if int(shares) > int(availableShares):
            return apology("Too many shares")

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type) values (?, ?, ?, ?, ?)",
                   session["user_id"], symbol, (int(shares) * (-1)), currentStatus["price"], "sell")

        print(currentStatus)
        sellAmount = int(shares) * int(currentStatus["price"])

        print(sellAmount)
        db.execute("UPDATE users SET cash = cash + ? where id = ?",
                   sellAmount, session["user_id"])
        return redirect("/")
    else:
        return render_template("sell.html", symbols=symbols)
