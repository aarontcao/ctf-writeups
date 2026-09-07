// Pinpoint: Guess the category from progressive clues
document.addEventListener('DOMContentLoaded', function () {
    var timerEl = document.getElementById('timer');
    var roundEl = document.getElementById('round');
    var clueEl = document.getElementById('clue');
    var scoreEl = document.getElementById('scoreDisplay');
    var optionsEl = document.getElementById('options');
    var resultEl = document.getElementById('result');
    var startTime = Date.now();
    var timerInterval;
    var done = false;
    var totalScore = 0;

    // Multiple rounds of puzzles
    var puzzles = [
        {
            clues: ['Python', 'Java', 'Rust', 'C++', 'Go'],
            answer: 'Programming Languages',
            options: ['Programming Languages', 'Snake Species', 'Coffee Brands', 'Board Games']
        },
        {
            clues: ['Fork', 'Branch', 'Merge', 'Push', 'Commit'],
            answer: 'Git Commands',
            options: ['Kitchen Tools', 'Git Commands', 'Tree Parts', 'Exercise Moves']
        },
        {
            clues: ['Port', 'Socket', 'Packet', 'Router', 'Firewall'],
            answer: 'Networking Terms',
            options: ['Ship Parts', 'Networking Terms', 'Electrical Components', 'Construction Tools']
        },
        {
            clues: ['Stack', 'Queue', 'Heap', 'Tree', 'Graph'],
            answer: 'Data Structures',
            options: ['Office Supplies', 'Data Structures', 'Card Games', 'Landscape Features']
        },
        {
            clues: ['Phishing', 'Trojan', 'Worm', 'Ransomware', 'Rootkit'],
            answer: 'Cyber Threats',
            options: ['Fishing Equipment', 'Greek Mythology', 'Cyber Threats', 'Garden Pests']
        }
    ];

    var currentPuzzle = 0;
    var currentClue = 0;
    var answered = false;

    function render() {
        var p = puzzles[currentPuzzle];
        roundEl.textContent = 'Round ' + (currentPuzzle + 1) + ' of ' + puzzles.length + ' — Clue ' + (currentClue + 1) + ' of ' + p.clues.length;
        clueEl.textContent = p.clues[currentClue];
        scoreEl.textContent = 'Score: ' + totalScore;

        optionsEl.innerHTML = '';
        p.options.forEach(function (opt) {
            var btn = document.createElement('div');
            btn.className = 'pinpoint-option';
            btn.textContent = opt;
            if (!answered) {
                btn.addEventListener('click', function () {
                    onAnswer(opt, btn);
                });
            }
            optionsEl.appendChild(btn);
        });
    }

    function onAnswer(opt, btn) {
        if (answered) return;
        answered = true;
        var p = puzzles[currentPuzzle];

        // Disable all options
        var allOpts = optionsEl.querySelectorAll('.pinpoint-option');
        allOpts.forEach(function (o) { o.classList.add('disabled'); });

        if (opt === p.answer) {
            btn.classList.add('correct');
            // Points: more for fewer clues (5 for 1 clue, 4 for 2, etc.)
            var points = (p.clues.length - currentClue) * 20;
            totalScore += points;
            scoreEl.textContent = 'Score: ' + totalScore + ' (+' + points + ')';
        } else {
            btn.classList.add('wrong');
            // Highlight correct answer
            allOpts.forEach(function (o) {
                if (o.textContent === p.answer) o.classList.add('correct');
            });
        }

        // Move to next round after delay
        setTimeout(function () {
            currentPuzzle++;
            currentClue = 0;
            answered = false;
            if (currentPuzzle >= puzzles.length) {
                finishGame();
            } else {
                render();
            }
        }, 1500);
    }

    function finishGame() {
        done = true;
        clearInterval(timerInterval);
        var elapsed = Math.floor((Date.now() - startTime) / 1000);

        resultEl.className = 'game-result show';
        resultEl.style.background = '#e8f5e9';
        resultEl.innerHTML = '🎉 Game complete!<br>Final score: ' + totalScore + ' pts (' + timerEl.textContent + ')';

        clueEl.textContent = '🏁 Finished!';
        roundEl.textContent = '';
        optionsEl.innerHTML = '';

        fetch('/games/pinpoint/score', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ score: totalScore, time_seconds: elapsed })
        }).then(function (r) { return r.json(); }).then(function (data) {
            if (data.leaderboard) {
                renderInlineLeaderboard(document.getElementById('leaderboardContainer'), data.leaderboard, 'pinpoint');
            }
        });
    }

    function updateTimer() {
        if (done) return;
        var elapsed = Math.floor((Date.now() - startTime) / 1000);
        var min = Math.floor(elapsed / 60);
        var sec = elapsed % 60;
        timerEl.textContent = min + ':' + (sec < 10 ? '0' : '') + sec;
    }

    timerInterval = setInterval(updateTimer, 1000);

    // Auto-reveal next clue every 8 seconds if not answered
    setInterval(function () {
        if (done || answered) return;
        var p = puzzles[currentPuzzle];
        if (currentClue < p.clues.length - 1) {
            currentClue++;
            clueEl.textContent = p.clues.slice(0, currentClue + 1).join(' • ');
            roundEl.textContent = 'Round ' + (currentPuzzle + 1) + ' of ' + puzzles.length + ' — Clue ' + (currentClue + 1) + ' of ' + p.clues.length;
        }
    }, 8000);

    render();
});
