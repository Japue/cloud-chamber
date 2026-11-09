# Git Tutorial

Install git first
In the .gitignore file you can add files that are local to your system, e.g. a build folder, these files will not be commited to your repo and will be invisible to git

To get a github repo on your local machine do git clone link, and fill the link with the link of the github repo. Then if you have admin access you can also make changes in the github if you don't your changes will stay local or you will have to make your own github repo but it will be separate of the actual original github repo

## Change workflow

- git status: gives the current status of the repo
- git add .: adds all modified files to tracked files
- git commit -m "message": commits your changes to the repo locally
- git push: pushes all pending commits to github on the current branch
- change your main.cpp to always showcase the full program, including your last change, for example if adding a function that changes image to pixels, implement it in the main.cpp, if you then add video to image also implement into the main.cpp, don't forget the put new .cpps into the CMakeLists.txt

## Branches

For every new feature in development make a new branch, the main branch should always be a working version that isn't in development, to list all branches do git branch, to switch to another branch do git switch branch. You always start on main update your local system, make a new branch, update it's origin for the first time. This process is described below, fill in branch with your branch name, it should represent what youre working on:

- git switch main
- git pull
- git switch -c branch
- git push -u origin branch (only the first time)
- from then on you can always use git push and pull like in the Change workflow

## Merging branches

Branches are only for one feature, when it's done you should merge it into the main branch, ! don't forget to update the CMakeLists.txt and the main.cpp, always update the README.md on the main branch to avoid conflicts, also make sure before merging the program works and doesn't contain errors, if it does contain errors make a branch that's called something like "fixfeature".

For the merge you would go to main, update the system, merge and then push to put the merge on github.

- git switch main
- git pull
- git merge branch
- git push
