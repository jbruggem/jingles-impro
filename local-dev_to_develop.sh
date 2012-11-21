#!/bin/bash
git checkout develop
read -p "ok?"
git pull origin develop
read -p "ok?"
git checkout local-dev
read -p "ok?"
git rebase develop
read -p "ok?"
git checkout develop
echo -e "Please merge with a description of what you are merging: \
\n\tgit merge local-dev --no-ff -m \"[DESCRIPTION]\" \
\n\tgit push origin develop"
