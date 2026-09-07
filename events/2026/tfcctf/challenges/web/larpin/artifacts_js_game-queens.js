// Queens: Place one queen in each colored region on a 5x5 grid
// No two queens share a row, column, or touch diagonally
document.addEventListener('DOMContentLoaded', function () {
    var SIZE = 5;
    var grid = document.getElementById('queensGrid');
    var timerEl = document.getElementById('timer');
    var resultEl = document.getElementById('result');
    var startTime = Date.now();
    var timerInterval;
    var done = false;

    // Region colors (0-4), each region gets one queen
    var regions = [
        [0, 0, 1, 1, 1],
        [0, 0, 1, 2, 2],
        [3, 0, 1, 2, 2],
        [3, 3, 4, 4, 2],
        [3, 3, 4, 4, 4]
    ];

    // Solution: queen positions [row, col] for each region
    var solution = [
        [0, 3],  // region 0 -> row 2, col 0 (actually let's compute a valid one)
        [2, 0],  // region 1
        [4, 4],  // region 2
        [1, 2],  // region 3... let me pick a valid solution
        [3, 1]   // region 4
    ];
    // Valid solution: (0,3), (1,0), (2,2), (3,4), (4,1) - check no adjacency
    // Actually let me pick: r0c4, r1c1, r2c3, r3c0, r4c2
    solution = [[0, 4], [1, 1], [2, 3], [3, 0], [4, 2]];

    var state = []; // 0=empty, 1=queen
    for (var i = 0; i < SIZE; i++) {
        state[i] = [];
        for (var j = 0; j < SIZE; j++) {
            state[i][j] = 0;
        }
    }

    function render() {
        grid.innerHTML = '';
        for (var r = 0; r < SIZE; r++) {
            for (var c = 0; c < SIZE; c++) {
                var cell = document.createElement('div');
                cell.className = 'queens-cell r' + regions[r][c];
                if (state[r][c] === 1) {
                    cell.classList.add('placed');
                    cell.textContent = '👑';
                }
                cell.setAttribute('data-r', r);
                cell.setAttribute('data-c', c);
                if (!done) {
                    cell.addEventListener('click', onCellClick);
                }
                grid.appendChild(cell);
            }
        }
    }

    function onCellClick(e) {
        var el = e.currentTarget;
        var r = parseInt(el.getAttribute('data-r'));
        var c = parseInt(el.getAttribute('data-c'));
        state[r][c] = state[r][c] === 1 ? 0 : 1;
        render();
    }

    function updateTimer() {
        if (done) return;
        var elapsed = Math.floor((Date.now() - startTime) / 1000);
        var min = Math.floor(elapsed / 60);
        var sec = elapsed % 60;
        timerEl.textContent = min + ':' + (sec < 10 ? '0' : '') + sec;
    }

    timerInterval = setInterval(updateTimer, 1000);

    document.getElementById('resetBtn').addEventListener('click', function () {
        for (var i = 0; i < SIZE; i++) {
            for (var j = 0; j < SIZE; j++) {
                state[i][j] = 0;
            }
        }
        resultEl.className = 'game-result';
        render();
    });

    document.getElementById('checkBtn').addEventListener('click', function () {
        // Count queens
        var queens = [];
        for (var r = 0; r < SIZE; r++) {
            for (var c = 0; c < SIZE; c++) {
                if (state[r][c] === 1) queens.push([r, c]);
            }
        }

        if (queens.length !== SIZE) {
            resultEl.className = 'game-result show';
            resultEl.style.background = '#fff0f0';
            resultEl.textContent = 'Place exactly ' + SIZE + ' queens (one per region).';
            return;
        }

        // Check one per region
        var regionQueens = {};
        for (var i = 0; i < queens.length; i++) {
            var reg = regions[queens[i][0]][queens[i][1]];
            if (regionQueens[reg]) {
                resultEl.className = 'game-result show';
                resultEl.style.background = '#fff0f0';
                resultEl.textContent = '❌ Multiple queens in the same region!';
                return;
            }
            regionQueens[reg] = true;
        }

        // Check no shared rows/cols
        var rows = {}, cols = {};
        for (var i = 0; i < queens.length; i++) {
            if (rows[queens[i][0]] || cols[queens[i][1]]) {
                resultEl.className = 'game-result show';
                resultEl.style.background = '#fff0f0';
                resultEl.textContent = '❌ Two queens share a row or column!';
                return;
            }
            rows[queens[i][0]] = true;
            cols[queens[i][1]] = true;
        }

        // Check no diagonal adjacency
        for (var i = 0; i < queens.length; i++) {
            for (var j = i + 1; j < queens.length; j++) {
                var dr = Math.abs(queens[i][0] - queens[j][0]);
                var dc = Math.abs(queens[i][1] - queens[j][1]);
                if (dr <= 1 && dc <= 1) {
                    resultEl.className = 'game-result show';
                    resultEl.style.background = '#fff0f0';
                    resultEl.textContent = '❌ Two queens are touching (even diagonally)!';
                    return;
                }
            }
        }

        // All checks passed
        done = true;
        clearInterval(timerInterval);
        var elapsed = Math.floor((Date.now() - startTime) / 1000);
        var score = Math.max(100 - elapsed, 10);
        resultEl.className = 'game-result show';
        resultEl.style.background = '#e8f5e9';
        resultEl.textContent = '🎉 Solved! Score: ' + score + ' pts (' + timerEl.textContent + ')';

        fetch('/games/queens/score', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ score: score, time_seconds: elapsed })
        }).then(function (r) { return r.json(); }).then(function (data) {
            if (data.leaderboard) {
                renderInlineLeaderboard(document.getElementById('leaderboardContainer'), data.leaderboard, 'queens');
            }
        });
    });

    render();
});
