// Tango: Fill a 6x6 grid with suns (☀️) and moons (🌙)
// Rules: 3 of each per row/column, no 3 adjacent same symbol
document.addEventListener('DOMContentLoaded', function () {
    var SIZE = 6;
    var grid = document.getElementById('tangoGrid');
    var timerEl = document.getElementById('timer');
    var resultEl = document.getElementById('result');
    var startTime = Date.now();
    var timerInterval;
    var done = false;

    // Pre-filled puzzle (0=empty, 1=sun, 2=moon)
    var puzzle = [
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 2, 0],
        [2, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 1],
        [0, 2, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0]
    ];

    // Solution for validation
    var solution = [
        [2, 2, 1, 1, 2, 1],
        [1, 1, 2, 2, 2, 1],
        [2, 1, 1, 2, 1, 2],
        [1, 2, 2, 1, 1, 2],
        [1, 2, 1, 2, 1, 2],
        [2, 1, 2, 1, 2, 1]
    ];

    var state = [];
    for (var i = 0; i < SIZE; i++) {
        state[i] = [];
        for (var j = 0; j < SIZE; j++) {
            state[i][j] = puzzle[i][j];
        }
    }

    function render() {
        grid.innerHTML = '';
        for (var r = 0; r < SIZE; r++) {
            for (var c = 0; c < SIZE; c++) {
                var cell = document.createElement('div');
                cell.className = 'tango-cell';
                if (puzzle[r][c] !== 0) cell.classList.add('fixed');
                if (state[r][c] === 1) {
                    cell.classList.add('sun');
                    cell.textContent = '☀️';
                } else if (state[r][c] === 2) {
                    cell.classList.add('moon');
                    cell.textContent = '🌙';
                }
                cell.setAttribute('data-r', r);
                cell.setAttribute('data-c', c);
                if (puzzle[r][c] === 0 && !done) {
                    cell.addEventListener('click', onCellClick);
                }
                grid.appendChild(cell);
            }
        }
    }

    function onCellClick(e) {
        var r = parseInt(e.target.getAttribute('data-r'));
        var c = parseInt(e.target.getAttribute('data-c'));
        // Cycle: empty -> sun -> moon -> empty
        state[r][c] = (state[r][c] + 1) % 3;
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
                state[i][j] = puzzle[i][j];
            }
        }
        resultEl.className = 'game-result';
        resultEl.textContent = '';
        render();
    });

    document.getElementById('checkBtn').addEventListener('click', function () {
        // Check if complete
        var complete = true;
        for (var i = 0; i < SIZE; i++) {
            for (var j = 0; j < SIZE; j++) {
                if (state[i][j] === 0) complete = false;
            }
        }
        if (!complete) {
            resultEl.className = 'game-result show';
            resultEl.style.background = '#fff0f0';
            resultEl.textContent = 'Fill all cells first!';
            return;
        }

        // Validate against solution
        var correct = true;
        for (var i = 0; i < SIZE; i++) {
            for (var j = 0; j < SIZE; j++) {
                if (state[i][j] !== solution[i][j]) correct = false;
            }
        }

        if (correct) {
            done = true;
            clearInterval(timerInterval);
            var elapsed = Math.floor((Date.now() - startTime) / 1000);
            var score = Math.max(100 - elapsed, 10);
            resultEl.className = 'game-result show';
            resultEl.style.background = '#e8f5e9';
            resultEl.textContent = '🎉 Solved! Score: ' + score + ' pts (' + timerEl.textContent + ')';

            fetch('/games/tango/score', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ score: score, time_seconds: elapsed })
            }).then(function (r) { return r.json(); }).then(function (data) {
                if (data.leaderboard) {
                    renderInlineLeaderboard(document.getElementById('leaderboardContainer'), data.leaderboard, 'tango');
                }
            });
        } else {
            resultEl.className = 'game-result show';
            resultEl.style.background = '#fff0f0';
            resultEl.textContent = '❌ Not quite right. Keep trying!';
            // Highlight errors
            var cells = grid.querySelectorAll('.tango-cell');
            cells.forEach(function (cell) {
                var r = parseInt(cell.getAttribute('data-r'));
                var c = parseInt(cell.getAttribute('data-c'));
                if (state[r][c] !== solution[r][c]) {
                    cell.classList.add('error');
                }
            });
        }
    });

    render();
});
