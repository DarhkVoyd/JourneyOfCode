/* Toggle between adding and removing the "responsive" class to nav-list when the user clicks on the icon */
function myFunction() {
	var x = document.getElementById('nav-bar');
	var y = document.querySelector('h1');
	if (x.className === 'navigation' || y.className === 'logo') {
		x.className += ' responsive';
		y.className += ' responsive';
	} else {
		x.className = 'navigation';
		y.className = 'logo';
	}
    return true;
}