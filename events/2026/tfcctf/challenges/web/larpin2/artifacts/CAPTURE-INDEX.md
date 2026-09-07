# larpin2: capture index

Post-contest evidence capture. We walled larpin2 while it stood at 0 solves; it
finished at 7. Nothing here is a solve attempt.

- Instance: `larpbrev-9b2056ac0129030d.challs.ctf.thefewchosen.com`, started 13:28Z on 2026-09-06, TTL to 13:48Z.
- Account used: `cap0906` / "Capture Agent", registered through the site's own register toggle. A plain, non-premium account, which is the position every one of our sessions occupied.
- Practical note for anyone reproducing this: the landing page is a single form at `/auth` with two submit buttons, `name=action value=login` and `name=action value=register`. The register button is `display:none` until `#toggleRegisterBtn` is clicked, and `input[name=full_name]` is hidden until then too. Registration does not log you in; it 302s back to the landing page with "Registered successfully. Please login."

All files are in `live-2026-09-06/`, all taken 2026-09-06 between 13:36Z and 13:40Z.

| file | what it shows |
|---|---|
| `shot-01-landing-anon.png` | The anonymous landing page, sign-in card on the right. |
| `shot-01b-register-form.png` | The same card after clicking "New to LarpIn? Join now": the register form with `username`, `full_name` and `password` filled in. |
| `shot-01c-registered-ok.png` | The "Registered successfully. Please login." banner, proving the account was created rather than assumed. |
| `shot-02-feed.png` | The authenticated feed as `cap0906`. |
| `shot-03-premium.png` | `/premium`, the page holding the activation form. This is where a valid `premium_token` is cashed in, and on larpin the equivalent page produced the flag two seconds after a token was supplied. |
| `shot-04-profile-premium-user.png` | `/profile/bill.gates`, one of the seven seeded premium users. Shows the premium badge next to the name, which is the discriminator we used to tell premium rows from ordinary ones. |
| `shot-05-jobs.png` | `/jobs`, the job list. |
| `shot-06-job-1.png` | `/jobs/1`, the single admin-owned job on a fresh instance ("Senior Software Engineer"). The CV upload path we sent twelve XXE and SSRF payloads down hangs off this. |
| `shot-07-own-profile.png` | `/profile/cap0906`, our own profile: no premium badge. The control for the shot above. |
| `shot-08-messages.png` | `/messages`, where the automated rejection DM lands after a job application. |

## What is not here

No screenshot of a premium-activated view exists, because we never obtained a
valid `premium_token`. That is the whole reason larpin2 is in the unsolved
column, and an image of it would have to be fabricated.
