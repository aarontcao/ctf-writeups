(() => {
  'use strict';
  const $ = (id) => document.getElementById(id);
  const escape = (value) =>
    String(value).replace(
      /[&<>"']/g,
      (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' })[c],
    );
  let authenticated = false,
    poller = null;
  async function api(path, options = {}) {
    const response = await fetch(path, options);
    const payload = await response.json().catch(() => ({}));
    if (!response.ok) throw new Error(payload.error || `HTTP ${response.status}`);
    return payload;
  }
  function showLogin() {
    authenticated = false;
    $('login-panel').hidden = false;
    $('dashboard').hidden = true;
    $('identity').innerHTML = '';
    if (poller) {
      clearInterval(poller);
      poller = null;
    }
  }
  async function enter(user) {
    authenticated = true;
    $('login-panel').hidden = true;
    $('dashboard').hidden = false;
    $('identity').innerHTML =
      `<span class="signed-in">${escape(user.team_name)}</span><button id="logout" class="quiet">Sign out</button>`;
    $('logout').onclick = async () => {
      await api('/api/logout', { method: 'POST' });
      showLogin();
    };
    await refresh();
    if (poller) clearInterval(poller);
    poller = setInterval(refresh, 2000);
  }
  function teamCell(team) {
    if (team.own)
      return `<div class="team-name own-team"><strong>${escape(team.team_name)}</strong><small>YOU</small></div>`;
    if (team.replay_id)
      return `<div class="team-name replay-team"><strong>${escape(team.team_name)}</strong><span>WATCH &rarr;</span></div>`;
    return `<div class="team-name unavailable-team"><strong>${escape(team.team_name)}</strong></div>`;
  }
  function resultIcon(team) {
    if (team.own || !team.viewer_outcome) return '';
    if (team.viewer_outcome === 'draw')
      return '<span class="result-icon" title="You tied with this team" aria-label="You tied with this team">=</span>';
    return team.viewer_outcome === 'win'
      ? '<span class="result-icon" title="You won against this team" aria-label="You won against this team">&#x1F451;</span>'
      : '<span class="result-icon" title="You lost against this team" aria-label="You lost against this team">&#x1F480;</span>';
  }
  async function refresh() {
    if (!authenticated) return;
    try {
      const leaders = await api('/api/leaderboard');
      const table = $('leaderboard');
      table.innerHTML =
        leaders
          .map(
            (team) =>
              `<tr class="${team.own ? 'is-own' : ''}${team.replay_id ? ' has-replay' : ''}" ${team.replay_id ? `data-href="/replay/${team.replay_id}" tabindex="0" role="link" aria-label="Open latest replay against ${escape(team.team_name)}"` : ''}><td class="rank"><span>${team.rank}</span>${resultIcon(team)}</td><td>${teamCell(team)}</td><td>${team.wins}</td><td>${team.draws}</td><td>${team.losses}</td><td class="points">${team.points}</td></tr>`,
          )
          .join('') || '<tr><td colspan="6" class="muted empty-row">No ranked teams yet.</td></tr>';
      table.querySelectorAll('tr[data-href]').forEach((row) => {
        const open = () => location.assign(row.dataset.href);
        row.addEventListener('click', open);
        row.addEventListener('keydown', (event) => {
          if (event.key === 'Enter' || event.key === ' ') {
            event.preventDefault();
            open();
          }
        });
      });
    } catch (error) {
      if (error.message === 'authentication required') showLogin();
    }
  }
  $('login-form').addEventListener('submit', async (event) => {
    event.preventDefault();
    $('login-error').textContent = '';
    try {
      await enter(
        await api('/api/login', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ token: $('token').value }),
        }),
      );
    } catch (error) {
      $('login-error').textContent = error.message;
    }
  });
  $('upload-form').addEventListener('submit', async (event) => {
    event.preventDefault();
    const file = $('bot').files[0];
    if (!file) return;
    const names = [...document.querySelectorAll('.character-name')],
      classes = [...document.querySelectorAll('.character-class')];
    const loadout = names.map((name, i) => ({ name: name.value.trim(), class: classes[i].value }));
    const body = new FormData();
    body.append('bot', file);
    body.append('loadout', JSON.stringify(loadout));
    $('upload-status').textContent = 'Validating and accepting submission...';
    try {
      const result = await api('/api/bots', { method: 'POST', body });
      $('upload-status').textContent =
        `Version ${result.version} accepted as queue #${result.sequence}; ${result.opponents} matches snapshotted.`;
      $('bot').value = '';
      await refresh();
    } catch (error) {
      $('upload-status').textContent = error.message;
    }
  });
  api('/api/me').then(enter).catch(showLogin);
})();
