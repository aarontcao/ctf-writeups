(() => {
  'use strict';
  const BOXES = [
    [380, 180, 500, 300],
    [380, 300, 500, 420],
    [380, 780, 500, 900],
    [380, 900, 500, 1020],
    [680, 360, 800, 480],
    [680, 480, 800, 600],
    [680, 600, 800, 720],
    [680, 720, 800, 840],
    [1500, 180, 1620, 300],
    [1500, 300, 1620, 420],
    [1500, 780, 1620, 900],
    [1500, 900, 1620, 1020],
    [1200, 360, 1320, 480],
    [1200, 480, 1320, 600],
    [1200, 600, 1320, 720],
    [1200, 720, 1320, 840],
  ];
  const CLASS_NAMES = ['Warrior', 'Archer', 'Bandit'];
  const CLASS_ICONS = ['\u{1FA93}', '\u{1F3F9}', '\u{1F52B}'];
  const FOV = [
    { range: 350, half: Math.PI / 4 },
    { range: 900, half: (Math.PI * 75) / 180 },
    { range: 600, half: Math.PI / 3 },
  ];
  const $ = (id) => document.getElementById(id);
  const escape = (value) =>
    String(value).replace(
      /[&<>"']/g,
      (c) => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;' })[c],
    );
  const canvas = $('arena'),
    ctx = canvas.getContext('2d');
  let replay,
    index = 0,
    playhead = 0,
    playing = false,
    last = 0,
    speed = 1,
    markers = [],
    animationHandle = 0,
    playbackGeneration = 0;
  const normalizedIndex = (value) => {
    if (!replay?.ticks?.length) return 0;
    const number = Number(value);
    return Math.max(
      0,
      Math.min(replay.ticks.length - 1, Number.isFinite(number) ? Math.floor(number) : 0),
    );
  };
  const frame = () => replay?.ticks?.[normalizedIndex(index)] || null;
  const rate = () => {
    const value = Number(replay?.tick_rate);
    return Number.isFinite(value) && value > 0 ? value : 20;
  };
  const clamp = (value, min, max) => Math.max(min, Math.min(max, value));
  function timeLabel(tick, precise = false) {
    const seconds = tick / rate(),
      minutes = Math.floor(seconds / 60),
      whole = Math.floor(seconds % 60);
    return `${String(minutes).padStart(2, '0')}:${String(whole).padStart(2, '0')}${precise ? `.${String(Math.floor((seconds % 1) * 100)).padStart(2, '0')}` : ''}`;
  }

  function deriveMarkers() {
    const result = [];
    replay.ticks.forEach((current, i) => {
      const previous = i ? replay.ticks[i - 1] : null,
        tick = current.observation.tick;
      if (previous) {
        current.observation.friendly.forEach((character, slot) => {
          if (previous.observation.friendly[slot]?.alive && !character.alive)
            result.push({ index: i, tick, type: 'death', label: `${character.name} died` });
        });
        if (
          current.observation.score[0] !== previous.observation.score[0] ||
          current.observation.score[1] !== previous.observation.score[1]
        )
          result.push({
            index: i,
            tick,
            type: 'capture',
            label: `Point captured — ${current.observation.score.join(':')}`,
          });
      }
      (current.warnings || []).forEach((message) =>
        result.push({ index: i, tick, type: 'warning', label: message }),
      );
      if (current.warnings_truncated)
        result.push({
          index: i,
          tick,
          type: 'warning',
          label: `${current.warnings_truncated} more warnings`,
        });
    });
    const final = replay.ticks.at(-1);
    if (
      replay.result &&
      (replay.result.own_score !== final.observation.score[0] ||
        replay.result.enemy_score !== final.observation.score[1])
    )
      result.push({
        index: replay.ticks.length - 1,
        tick: replay.result.tick,
        type: 'capture',
        label: `Final point captured — ${replay.result.own_score}:${replay.result.enemy_score}`,
      });
    return result;
  }
  function buildTimeline() {
    markers = deriveMarkers();
    const holder = $('timeline-markers');
    holder.replaceChildren();
    const lastTick = Math.max(replay.ticks.at(-1).observation.tick, replay.result?.tick || 0);
    markers.forEach((marker) => {
      const button = document.createElement('button');
      button.className = `timeline-marker ${marker.type}`;
      button.style.left = `${(marker.tick / Math.max(1, lastTick)) * 100}%`;
      button.title = `Tick ${marker.tick}: ${marker.label}`;
      button.onclick = () => setIndex(marker.index);
      holder.appendChild(button);
    });
    $('timeline').max = replay.ticks.length - 1;
    $('duration').textContent = `00:00 / ${timeLabel(lastTick)}`;
  }

  function drawFov(character) {
    const spec = FOV[character.class] || FOV[0],
      angle = Math.atan2(character.facing[1], character.facing[0]);
    ctx.beginPath();
    ctx.moveTo(character.x, character.y);
    ctx.arc(character.x, character.y, spec.range, angle - spec.half, angle + spec.half);
    ctx.closePath();
    ctx.fillStyle = 'rgba(215,70,37,.045)';
    ctx.fill();
    ctx.strokeStyle = 'rgba(215,70,37,.2)';
    ctx.lineWidth = 2;
    ctx.stroke();
  }
  function drawCharacter(character, friendly) {
    if (friendly && !character.alive) {
      ctx.strokeStyle = '#777168';
      ctx.lineWidth = 6;
      ctx.beginPath();
      ctx.moveTo(character.x - 15, character.y - 15);
      ctx.lineTo(character.x + 15, character.y + 15);
      ctx.moveTo(character.x + 15, character.y - 15);
      ctx.lineTo(character.x - 15, character.y + 15);
      ctx.stroke();
      return;
    }
    const color = friendly ? '#d74625' : '#2962a3';
    ctx.fillStyle = friendly ? 'rgba(215,70,37,.15)' : 'rgba(41,98,163,.15)';
    ctx.strokeStyle = color;
    ctx.lineWidth = 5;
    ctx.beginPath();
    ctx.arc(character.x, character.y, 27, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
    const facing = character.facing || [0, 0],
      length = Math.hypot(...facing) || 1;
    ctx.beginPath();
    ctx.moveTo(character.x, character.y);
    ctx.lineTo(character.x + (facing[0] / length) * 43, character.y + (facing[1] / length) * 43);
    ctx.stroke();
    ctx.font = '25px "Segoe UI Emoji",sans-serif';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText(CLASS_ICONS[character.class] || '?', character.x, character.y + 1);
    ctx.font = '700 17px Inter,sans-serif';
    ctx.textBaseline = 'alphabetic';
    ctx.fillStyle = color;
    ctx.fillText(character.name, character.x, character.y - 39);
  }
  function drawArrow(arrow) {
    const length = Math.hypot(...arrow.velocity) || 1;
    ctx.strokeStyle = arrow.owner ? '#2962a3' : '#d74625';
    ctx.lineWidth = 5;
    ctx.beginPath();
    ctx.moveTo(arrow.x, arrow.y);
    ctx.lineTo(
      arrow.x - (arrow.velocity[0] / length) * 30,
      arrow.y - (arrow.velocity[1] / length) * 30,
    );
    ctx.stroke();
  }
  function drawEvent(event) {
    const color = event.owner ? '#2962a3' : '#d74625';
    if (event.type === 3 && event.direction) {
      const length = Math.hypot(...event.direction) || 1;
      ctx.save();
      ctx.strokeStyle = color;
      ctx.globalAlpha = 0.78;
      ctx.lineWidth = 5;
      ctx.beginPath();
      ctx.moveTo(event.x, event.y);
      ctx.lineTo(
        event.x + (event.direction[0] / length) * 3200,
        event.y + (event.direction[1] / length) * 3200,
      );
      ctx.stroke();
      ctx.restore();
      return;
    }
    ctx.strokeStyle = event.type === 4 ? '#e49b16' : color;
    ctx.lineWidth = 4;
    ctx.beginPath();
    ctx.arc(event.x, event.y, event.type === 4 ? 38 : 30, 0, Math.PI * 2);
    ctx.stroke();
  }
  function drawIntent(character, action) {
    if (!character?.alive || !action) return;
    const length = Math.hypot(...action.move);
    if (length) {
      ctx.save();
      ctx.strokeStyle = 'rgba(28,29,31,.3)';
      ctx.setLineDash([8, 7]);
      ctx.lineWidth = 2;
      ctx.beginPath();
      ctx.moveTo(character.x, character.y);
      ctx.lineTo(
        character.x + (action.move[0] / length) * 58,
        character.y + (action.move[1] / length) * 58,
      );
      ctx.stroke();
      ctx.restore();
    }
  }

  function drawArena() {
    const current = frame(),
      observation = current.observation,
      progress = clamp(observation.capture_progress, -100, 100);
    ctx.setTransform(canvas.width / 2000, 0, 0, canvas.height / 1200, 0, 0);
    ctx.clearRect(0, 0, 2000, 1200);
    ctx.fillStyle = '#f7f1e7';
    ctx.fillRect(0, 0, 2000, 1200);
    ctx.strokeStyle = 'rgba(90,82,72,.13)';
    ctx.lineWidth = 1;
    for (let x = 0; x <= 2000; x += 100) {
      ctx.beginPath();
      ctx.moveTo(x, 0);
      ctx.lineTo(x, 1200);
      ctx.stroke();
    }
    for (let y = 0; y <= 1200; y += 100) {
      ctx.beginPath();
      ctx.moveTo(0, y);
      ctx.lineTo(2000, y);
      ctx.stroke();
    }
    ctx.fillStyle =
      progress > 0
        ? 'rgba(215,70,37,.16)'
        : progress < 0
          ? 'rgba(41,98,163,.16)'
          : 'rgba(228,155,22,.12)';
    ctx.strokeStyle = progress > 0 ? '#d74625' : progress < 0 ? '#2962a3' : '#e49b16';
    ctx.lineWidth = 5;
    ctx.beginPath();
    ctx.arc(1000, 600, 120, 0, Math.PI * 2);
    ctx.fill();
    ctx.stroke();
    if (progress) {
      ctx.fillStyle = progress > 0 ? 'rgba(215,70,37,.28)' : 'rgba(41,98,163,.28)';
      ctx.beginPath();
      ctx.arc(1000, 600, (120 * Math.abs(progress)) / 100, 0, Math.PI * 2);
      ctx.fill();
    }
    ctx.fillStyle = '#c9bda9';
    ctx.strokeStyle = '#1c1d1f';
    ctx.lineWidth = 3;
    BOXES.forEach((box) => {
      ctx.fillRect(box[0], box[1], box[2] - box[0], box[3] - box[1]);
      ctx.strokeRect(box[0], box[1], box[2] - box[0], box[3] - box[1]);
    });
    observation.friendly.filter((character) => character.alive).forEach(drawFov);
    (observation.events || []).forEach(drawEvent);
    (observation.arrows || []).forEach(drawArrow);
    observation.friendly.forEach((character) => drawCharacter(character, true));
    observation.enemies.forEach((character) => drawCharacter(character, false));
    (current.actions || []).forEach((action, slot) =>
      drawIntent(observation.friendly[slot], action),
    );
  }

  function render() {
    const current = frame();
    if (!current?.observation) return;
    index = normalizedIndex(index);
    const observation = current.observation,
      lastTick = Math.max(replay.ticks.at(-1).observation.tick, replay.result?.tick || 0),
      terminal = index === replay.ticks.length - 1 && replay.result?.tick > observation.tick,
      shownTick = terminal ? replay.result.tick : observation.tick,
      shownScore = terminal
        ? [replay.result.own_score, replay.result.enemy_score]
        : observation.score;
    drawArena();
    $('own-score').textContent = shownScore[0];
    $('enemy-score').textContent = shownScore[1];
    $('tick').textContent = `TICK ${shownTick}`;
    $('clock').textContent = timeLabel(shownTick, true);
    $('duration').textContent = `${timeLabel(shownTick)} / ${timeLabel(lastTick)}`;
    const progress = clamp(observation.capture_progress, -100, 100);
    $('capture-fill').style.left = progress < 0 ? `${50 + progress / 2}%` : '50%';
    $('capture-fill').style.width = `${Math.abs(progress) / 2}%`;
    $('capture-fill').style.background = progress < 0 ? 'var(--enemy)' : 'var(--friendly)';
    $('capture-label').textContent = terminal
      ? 'MATCH COMPLETE'
      : observation.capture_lock
        ? `POINT LOCKED · ${observation.capture_lock} TICKS`
        : progress
          ? `${progress > 0 ? 'YOU' : 'OPPONENT'} · ${Math.abs(progress)}%`
          : 'POINT NEUTRAL';
    $('timeline').value = index;
    $('roster').innerHTML = observation.friendly
      .map((character) => {
        const max = character.class === 0 ? 200 : 100,
          hp = clamp((character.hp / max) * 100, 0, 100);
        return `<article class="character-card ${character.alive ? '' : 'dead'}"><div class="class-icon">${CLASS_ICONS[character.class] || '?'}</div><div><div class="character-name">${escape(character.name)}</div><div class="character-meta">${CLASS_NAMES[character.class]} · ${character.alive ? `AMMO ${character.ammo}` : `RESPAWN ${character.respawn_ticks}`}</div></div><div class="hp">${character.hp} HP<div class="hp-bar"><i style="width:${hp}%"></i></div></div></article>`;
      })
      .join('');
    const warnings = [];
    for (let i = 0; i <= index; i++) {
      const replayFrame = replay.ticks[i];
      if (!replayFrame) continue;
      replayFrame.warnings.forEach((message) =>
        warnings.push({ index: i, tick: replayFrame.observation.tick, message }),
      );
      if (replayFrame.warnings_truncated)
        warnings.push({
          index: i,
          tick: replayFrame.observation.tick,
          message: `${replayFrame.warnings_truncated} additional warnings omitted`,
        });
    }
    $('warning-count').textContent = warnings.length;
    $('warnings').innerHTML =
      warnings
        .slice(-40)
        .reverse()
        .map(
          (item) =>
            `<button class="warning-item" data-index="${item.index}"><span class="warning-tick">T${item.tick}</span><span>${escape(item.message)}</span></button>`,
        )
        .join('') || '<div class="empty">No warnings up to this tick.</div>';
    $('warnings')
      .querySelectorAll('.warning-item')
      .forEach((element) => (element.onclick = () => setIndex(Number(element.dataset.index))));
  }
  function setIndex(value) {
    index = normalizedIndex(value);
    playhead = index;
    render();
  }
  function seekEvent(direction) {
    const ordered = [...new Map(markers.map((marker) => [marker.index, marker])).values()];
    const target =
      direction > 0
        ? ordered.find((marker) => marker.index > index)
        : ordered.reverse().find((marker) => marker.index < index);
    if (target) setIndex(target.index);
  }
  function setPlaying(value) {
    if (!replay?.ticks?.length) return;
    if (value && normalizedIndex(index) === replay.ticks.length - 1) setIndex(0);
    playing = Boolean(value);
    $('play').textContent = playing ? 'Ⅱ' : '▶';
    index = normalizedIndex(index);
    playhead = index;
    ++playbackGeneration;
    if (animationHandle) {
      cancelAnimationFrame(animationHandle);
      animationHandle = 0;
    }
    if (playing) {
      last = performance.now();
      const generation = playbackGeneration;
      animationHandle = requestAnimationFrame((now) => animate(now, generation));
    }
  }
  function animate(now, generation) {
    if (!playing || generation !== playbackGeneration) return;
    animationHandle = 0;
    const timestamp = Number(now),
      elapsed = Number.isFinite(timestamp) ? clamp((timestamp - last) / 1000, 0, 0.25) : 0,
      lastIndex = replay.ticks.length - 1,
      activeSpeed = Number.isFinite(Number(speed)) ? Number(speed) : 1;
    last = Number.isFinite(timestamp) ? timestamp : last;
    playhead = clamp(
      (Number.isFinite(playhead) ? playhead : index) + elapsed * rate() * activeSpeed,
      0,
      lastIndex,
    );
    const next = normalizedIndex(playhead);
    if (next !== index) {
      index = next;
      render();
    }
    if (index >= lastIndex) {
      setPlaying(false);
      return;
    }
    animationHandle = requestAnimationFrame((value) => animate(value, generation));
  }

  fetch(`/api/replays/${MATCH_ID}/file`)
    .then((response) => {
      if (!response.ok)
        throw Error(response.status === 401 ? 'Sign in to view this replay.' : 'Replay not found.');
      return response.arrayBuffer();
    })
    .then(parseCtfReplay)
    .then((value) => {
      replay = value;
      if (!replay.ticks.length) throw Error('Replay contains no ticks.');
      $('replay-status').hidden = true;
      $('timeline').oninput = () => setIndex(Number($('timeline').value));
      $('play').onclick = () => setPlaying(!playing);
      $('back').onclick = () => setIndex(index - rate() * 5);
      $('forward').onclick = () => setIndex(index + rate() * 5);
      $('previous-event').onclick = () => seekEvent(-1);
      $('next-event').onclick = () => seekEvent(1);
      $('speed').onchange = () => (speed = Number($('speed').value));
      buildTimeline();
      render();
    })
    .catch((error) => {
      $('replay-status').classList.add('error');
      $('replay-status').textContent = error.message;
    });
})();
