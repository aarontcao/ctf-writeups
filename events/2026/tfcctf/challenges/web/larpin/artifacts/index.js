document.addEventListener('DOMContentLoaded', function () {
    var btn = document.getElementById('toggleRegisterBtn');
    if (btn) btn.addEventListener('click', toggleRegister);
});

function toggleRegister() {
    var nameGroup = document.getElementById('fullNameGroup');
    var startBtn = document.querySelector('button[value="login"]');
    var regBtn = document.getElementById('realRegisterBtn');
    var toggleBtn = document.getElementById('toggleRegisterBtn');
    var title = document.querySelector('h2');
    var subtitle = document.querySelector('.t-muted');

    if (nameGroup.style.display === 'none') {
        nameGroup.style.display = 'block';
        startBtn.style.display = 'none';
        regBtn.style.display = 'block';
        regBtn.className = 'btn btn-primary';
        regBtn.style.width = '100%';
        regBtn.style.borderRadius = '24px';
        regBtn.style.padding = '12px';
        regBtn.style.fontSize = '16px';
        regBtn.textContent = 'Agree & Join';
        title.textContent = 'Sign up';
        subtitle.textContent = 'Make the most of your professional life';
        toggleBtn.textContent = 'Already on LarpIn? Sign in';
    } else {
        nameGroup.style.display = 'none';
        startBtn.style.display = 'block';
        regBtn.style.display = 'none';
        title.textContent = 'Sign in';
        subtitle.textContent = 'Stay updated on your professional world';
        toggleBtn.textContent = 'New to LarpIn? Join now';
    }
}
