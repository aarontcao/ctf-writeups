document.addEventListener('DOMContentLoaded', function () {
    document.querySelectorAll('[data-job]').forEach(function (el) {
        el.addEventListener('click', function (e) {
            e.preventDefault();
            var id = el.getAttribute('data-job');
            var form = document.getElementById(id + '-apply');
            document.querySelectorAll('[id$="-apply"]').forEach(function (f) {
                if (f !== form) f.style.display = 'none';
            });
            form.style.display = form.style.display === 'block' ? 'none' : 'block';
        });
    });
});


