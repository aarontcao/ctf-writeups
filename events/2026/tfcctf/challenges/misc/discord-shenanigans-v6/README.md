# Discord Shenanigans v6

| | |
|---|---|
| Event | The Few Chosen CTF 2026 |
| Category | misc |
| Difficulty | baby |
| Author | hofill |
| Points at close | 50 |
| Solves | 265 |
| Status | solved |

> You already know. We don't want this challenge to be guessy. Wrap the hidden word in TFCCTF{}. It's in #announcements.

<details>
<summary><b>Solution</b></summary>

## Solution

The hidden word is an acrostic. The six sentences in the previous day's `#announcements` post start with Come, Assemble, Stay, The, Let, Everyone, which spells CASTLE. The @everyone line and the closing link don't count.

![top: the title and a line naming the two panels; left: the #announcements post with the first letter of each sentence boxed in red; right: the six sentence initials, the word CASTLE, the flag, and a note that the message is plain ASCII](media/05-insight-acrostic.png)

## The Unicode dead end

A hidden word in a chat message smells like Unicode stego, so I checked for non-ASCII codepoints first.

![top: the #announcements channel header; middle: Noria's post, with the @everyone opening line and the six sentences below it; bottom: the event link](media/03-recon-announcement.png)

A scan of my transcription came back empty. But I transcribed it from a screenshot, which can't show invisible characters, so that only proves the visible text is plain ASCII.

Flag: `TFCCTF{CASTLE}`
</details>
