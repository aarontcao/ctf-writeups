document.addEventListener('DOMContentLoaded', function () {
    var editBtn = document.getElementById('toggleEditBtn');
    var cancelBtn = document.getElementById('cancelEditBtn');

    function toggleEdit() {
        var form = document.getElementById('editForm');
        form.style.display = form.style.display === 'block' ? 'none' : 'block';
    }

    if (editBtn) editBtn.addEventListener('click', toggleEdit);
    if (cancelBtn) cancelBtn.addEventListener('click', toggleEdit);

    // Sanitize user-generated content before rendering
    document.querySelectorAll('.profile-content').forEach(function (el) {
        var raw = decodeURIComponent(el.getAttribute('data-raw') || '');
        el.innerHTML = DOMPurify.sanitize(raw);
    });
});
