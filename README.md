# RemC
rem (short for remember) is a simple CLI tool designed to store, search, and manage your frequently used shell commands and code snippets without consuming unnecessary system resources.
Built in pure C with zero external dependencies, it boasts a near-zero memory footprint and instantaneous execution—making it the ideal utility for minimalist terminal workflows and systems running resource-heavy local AI models.

##HOW TO INSTALL

```bash
git clone [https://github.com/aresthebellator/RemC.git](https://github.com/aresthebellator/RemC.git)
cd RemC
gcc rem.c -o rem
sudo mv rem /usr/local/bin/
```

##EXAMPLE TO USE

```bash
#add new rem
rem add "launch-ollama" "ollama run"
rem add "system update in Ubuntu" "sudo apt upgrade"

#how to see all the rem
rem list

#search for a specific rem
rem find "ollama"
