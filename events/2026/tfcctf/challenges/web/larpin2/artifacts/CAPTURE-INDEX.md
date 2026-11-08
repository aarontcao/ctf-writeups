# larpin2: capture index

I took these after the contest, and they show recon only. All files are in `live-2026-09-06/`, from one instance. The table skips shot-01-landing.png, an earlier capture of the landing page.

I used `cap0906`, a plain non-premium account. The landing page is one form at `/auth` with two submit buttons, `name=action value=login`, and `name=action value=register`. The register button and `input[name=full_name]` stay hidden until you click `#toggleRegisterBtn`. Registering doesn't log you in.

| file | what it shows |
|---|---|
| `shot-01-landing-anon.png` | The anonymous landing page, sign-in card on the right. |
| `shot-01b-register-form.png` | The same card after clicking "New to LarpIn? Join now": the register form with `username`, `full_name`, and `password` filled in. |
| `shot-01c-registered-ok.png` | The "Registered successfully. Please login." banner, which shows the account exists. |
| `shot-02-feed.png` | The authenticated feed as `cap0906`. |
| `shot-03-premium.png` | `/premium`, the page holding the activation form. This is where a valid `premium_token` is cashed in, and on larpin the equivalent page produced the flag two seconds after a token was supplied. |
| `shot-04-profile-premium-user.png` | `/profile/bill.gates`, one of the seven seeded premium users. Shows the premium badge next to the name, which tells premium rows from ordinary ones. |
| `shot-05-jobs.png` | `/jobs`, the job list. |
| `shot-06-job-1.png` | `/jobs/1`, the single admin-owned job on a fresh instance ("Senior Software Engineer"). The CV upload path hangs off this page. |
| `shot-07-own-profile.png` | `/profile/cap0906`, the account's own profile, without a premium badge. The control for the shot above. |
| `shot-08-messages.png` | `/messages`, where the automated rejection DM lands after a job application. |

## Missing on purpose

There's no screenshot of a premium-activated view, because I never got a valid `premium_token`.
