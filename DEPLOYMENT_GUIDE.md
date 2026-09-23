# Deployment Guide — Presenting the Address Book Prototype

Four ways to demo the project to your evaluator, from simplest to most impressive.

| Option | What you show | Needs internet? | Effort |
|---|---|---|---|
| 1. Local EXE demo | The real C++ program | No | 1 min |
| 2. Netlify Drop link | Browser GUI prototype, shareable URL | Yes | 2 min |
| 3. GitHub Pages link | Same GUI on your own GitHub URL | Yes | 10 min |
| 4. Video backup | Recording in case tech fails | No | 5 min |

**Recommended combo for evaluation day:** run the **EXE live** (proves it's real C++) and keep the **Netlify link** open in a browser tab as your "prototype dashboard". Mention the web version as the listed "GUI enhancement" — it directly maps to your report's Enhancements section.

---

## Option 1 — Local EXE demo (always works, no internet)

**What's already prepared in your project folder:**

- `address_book.exe` — now a **static standalone build** (~2.8 MB). It runs on ANY Windows PC — lab machines, evaluator's laptop — with **no compiler, no Code::Blocks, nothing to install**.
- `Run_AddressBook.bat` — double-click launcher with a title banner; keeps the window open after exit.

**Steps:**
1. Copy the whole project folder to a **pendrive**.
2. On the demo PC, double-click `Run_AddressBook.bat`.
3. Demo script (5 minutes):
   - Add contact `Rahul Sharma` → show success message
   - Try an invalid phone (`abcd1234`) → show validation reject, then enter valid one
   - Display contacts → show the stored record
   - Search `RAHUL SHARMA` in capital letters → show case-insensitive match
   - Delete it → search again → `Contact Not Found!` → Display → empty message
   - Press `5` → clean exit

**Fallback:** if the lab PC blocks unknown executables, recompile there from `address_book.cpp` (any C++ compiler accepts it) — compile command is in `README.md`.

---

## Option 2 — Netlify Drop (fastest shareable link, ~2 minutes)

Puts your web prototype online with a public URL — no account needed.

1. Go to **https://app.netlify.com/drop**
2. Drag-and-drop your project's **`web` folder** onto the page
3. Netlify gives you a live URL like `https://sparkling-addressbook-12345.netlify.app`
4. Open that link on any phone/laptop — the prototype loads instantly

You can rename the site later (Site settings → Change site name) to something like `yourname-addressbook.netlify.app`. The link stays live for 1 hour on a free anonymous session — create a free account to keep it permanently.

---

## Option 3 — GitHub Pages (permanent link, looks professional)

> Note: your current folder sits in a Desktop git repo with no remote and some permission-noise. Cleanest approach: create a **fresh repository just for the project**.

1. Create a new repo on **github.com** → New → name it `address-book-system` → Public → Create (do NOT initialize with README).
2. In a terminal inside your project folder:
   ```bash
   git init
   git add address_book.cpp README.md PROJECT_REPORT.md VIVA_QUESTIONS.md web/index.html Run_AddressBook.bat DEPLOYMENT_GUIDE.md
   git commit -m "Address Book System - C++ mini project with web prototype"
   git branch -M main
   git remote add origin https://github.com/<your-username>/address-book-system.git
   git push -u origin main
   ```
3. On GitHub: repo → **Settings → Pages** → Source: `Deploy from a branch` → Branch: `main`, folder `/ (root)` → Save.
4. Wait 1–2 minutes → your site is live at:
   `https://<your-username>.github.io/address-book-system/web/`
5. Bonus: the repo itself doubles as your **submission artifact** — evaluator can see the source, report, and viva prep in one place. Paste the repo link on your report's cover page (optional).

---

## Option 4 — Video backup (5 minutes of insurance)

1. Press `Win + G` (Xbox Game Bar) or use `Win + Alt + R` to record the screen.
2. Record the full Option-1 demo script once, end to end.
3. Save the `.mp4` in the project folder and on your phone.
4. If the lab machine fails on demo day, play the video — evaluators accept this readily.

---

## Presentation tips for the evaluator

- **Open with the problem statement** (one line): "Manual contact diaries are slow to search — this system stores, finds, and removes contacts instantly using structures."
- **Show the code, not just output:** open `address_book.cpp` and point to `struct Contact` and `searchContact()` — evaluators want to see *your* structures and loops.
- **Map demo to theory:** as you demo each menu action, name the module (Module 1: Add...) and the concept (array of structures, linear search, string validation).
- **Know your numbers:** search complexity O(n), delete O(n), capacity `MAX_CONTACTS = 100`, menu is a do-while loop.
- **Close with enhancements:** "Data persistence via files, sorting, and this GUI prototype are the future scope — the GUI is already implemented as a prototype."
- Viva safety net: `VIVA_QUESTIONS.md` covers 42 likely questions with answers — read it the night before.

---

## File checklist for submission

| File | Purpose |
|---|---|
| `address_book.cpp` | Source code (print 2 copies for the record) |
| `address_book.exe` | Standalone demo binary |
| `Run_AddressBook.bat` | Easy launcher |
| `PROJECT_REPORT.md` | The written report (convert to PDF for print: open in VS Code → Markdown PDF extension, or paste into Google Docs → Download as PDF) |
| `VIVA_QUESTIONS.md` | Your prep sheet |
| `web/index.html` | GUI prototype (also hosted online via Options 2/3) |
| `DEPLOYMENT_GUIDE.md` | This guide |
