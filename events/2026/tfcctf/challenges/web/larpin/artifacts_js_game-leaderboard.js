// Shared utility: render leaderboard inline after game completion
function renderInlineLeaderboard(container, leaderboard, gameName) {
    var html = '<div style="margin-top: 20px; text-align: left;">';
    html += '<div style="font-size: 16px; font-weight: 700; margin-bottom: 12px; text-align: center;">🏆 Leaderboard</div>';

    if (leaderboard.length === 0) {
        html += '<div style="text-align: center; color: rgba(0,0,0,0.6); font-size: 14px;">No scores yet</div>';
    } else {
        leaderboard.forEach(function (s, i) {
            var medal = i === 0 ? '🥇' : i === 1 ? '🥈' : i === 2 ? '🥉' : (i + 1);
            var min = Math.floor(s.time_seconds / 60);
            var sec = s.time_seconds % 60;
            var timeStr = min + ':' + (sec < 10 ? '0' : '') + sec;

            html += '<div style="display: flex; align-items: center; padding: 8px 12px; border-bottom: 1px solid #e0dfdc; gap: 12px;">';
            html += '<div style="width: 28px; font-size: 16px; font-weight: 700; text-align: center;">' + medal + '</div>';
            html += '<div style="width: 36px; height: 36px; border-radius: 50%; background: #53626f; color: white; display: flex; align-items: center; justify-content: center; font-size: 14px; font-weight: 600; flex-shrink: 0;">' + (s.full_name ? s.full_name.charAt(0).toUpperCase() : '?') + '</div>';
            html += '<div style="flex: 1; font-size: 14px; font-weight: 600;">' + escapeHtmlLb(s.full_name) + '</div>';
            html += '<div style="font-size: 12px; color: rgba(0,0,0,0.6);">' + timeStr + '</div>';
            html += '<div style="font-size: 14px; font-weight: 700; color: #0a66c2; min-width: 50px; text-align: right;">' + s.score + ' pts</div>';
            html += '</div>';
        });
    }

    html += '<div style="text-align: center; margin-top: 12px;">';
    html += '<a href="/games/leaderboard/' + gameName + '" style="color: #0a66c2; font-weight: 600; text-decoration: none; font-size: 14px;">View full leaderboard →</a>';
    html += '</div></div>';

    container.innerHTML += html;
}

function escapeHtmlLb(s) {
    var div = document.createElement('div');
    div.textContent = s || '';
    return div.innerHTML;
}
