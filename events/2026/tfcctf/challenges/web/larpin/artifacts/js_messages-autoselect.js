// Auto-select chat thread based on URL parameter
document.addEventListener('DOMContentLoaded', function () {
    const autoSelectEl = document.getElementById('autoSelectUser');
    if (autoSelectEl) {
        const userId = autoSelectEl.getAttribute('data-user-id');
        const userItem = document.querySelector('.thread-item[data-user-id="' + userId + '"]');
        if (userItem) {
            userItem.click();
        }
    }
});
