# minishell
Our great minishell project

General rules for our repository:

minishell/
├── src/
├── include/
├── Makefile
├── README.md
└── .gitignore

- Repository: 
	git clone https://github.com/Alexxxito7/minishell.git

- Daily Workflow Checklist: 
	see under Projects - ToDo | In Progress | Done

- With every start, pull code (main branch) + create new branch (e.g. for every feature): 
	git pull origin main
	git checkout -b feature/parser
	
- Add/Commit/Push
	git add .
	git commit -m "Add parser function"
	git push origin feature/parser

- Return to main branch and get update:
	git checkout main
	git pull origin main

- Review our codes in Github:
	GitHub Pull Request
	Go to GitHub → Pull Request → New PR → Create PR → Merge when approved
	
	Alternatively through command line:
		git checkout main
		git pull origin main
		git merge feature/lexer
		git push origin main

- Delete merged branches:
	git branch -d feature/lexer
	git push origin --delete feature/lexer


DAILY FLOW RECAP

→ Every Day We Work

→ git pull origin main – get the latest changes

→ git checkout -b feature/something (if new task)

→ Do your work

→ git add . && git commit -m "added extra feature"

→ git push origin feature/extra

→ Create Pull Request on GitHub: (or notify your teammate)

→ Merge once reviewed

→ Delete the old branch (locally and on GitHub)

