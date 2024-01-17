The Locksmith

#### Video Demo: https://www.youtube.com/watch?v=uY5XaRdT7cE

#### Description:

This python-based web app called The Locksmith is a password manager which uses jinga, flask, sql technologies to enable users to save all their passwords at one place and leave the worries to remember all passwords behind.

-Technologies and webstacks used:

    1. HTML5
    2. CSS3
    3. Flask
    4. SQLite3
    5. other small libraries or packages

This uses the flask frame work so its follow the following directories and files:

1. static/ - This contain a favicon file which is responsible for the favicon shown on the webpage tab in the browser. I have choosen it to be lock because I have given the name of locksmith to the app. It also contains the style.css file which is the stylesheet responsible to design the html pages. This directories basically contains all types of static files.

2. templates/ - This directory contains all the html pages. Mainly the layout.html file. This file gives the main layout structure to the web app. This also contains other pages such as apology.html which is inspired from CS50 finance to handle errors in this project. The index.html contains all the main contents and information. login.html and register.html contains the forms and inputs regarding the login and register respectively.

3. requirements.txt - This .txt file contains all python module required for this project.

4. app.py - This is the main Python file which renders the web app using the Flask framework and is responsible for backend handling such as database manipulation, session management, rendering templates.

5. helpers.py- This is the additional Python file where extra functions such as login_required and apology are defined.

I have decided to go Flask because it is a light weight framework and following through the course I have gotten really comfortable with flask and Since I have complete another CS50 course in Python I feel comfortable enough in Python.

Explanation of the web-app functioning-

This is a simple to use app. Any user can register for an account by providing an Username and Password, the password is converted into a hash using werkzueg. Then it is checked if an user already exists with given username if exists then it gives an error else it registers the users and saves the username and hashed pasword in the database. Once the user is logged-in the user can store username and passwords for various websites.

Routing

The app.route function is decorated with the @login_required function which makes sure that the user is logged-in and their user-id is stored in session file management and when manipulationing the database the user is authenticated using the user-id for authenticated user.

Sessions

The web-app uses sessions to authenticate and check if a user is registered. Here, the session is configued to use filesystem (instead of signed cookies). As the user logins, their username and password are cross-checked with the database and the password is matched with the hashed password again using Werkzeug module. After all is confirmed and checked to be correct the user is logged in and a session is created and the user_id of the user is stored in the session and any further requests to the server are excuted with the logged in user so that all credentials are added to appropriate user.

Database

Sqlite is used to manage database which stores all registered users and locks i.e. the user data consisting of usernames and passwords to various websites. Foreign keys and references are used to connect the two tables users and their locks.
