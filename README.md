Readme added after first commit

Wrlinb git guide:

1. Download git repo:
	git clone https://github.com/Gettor/ClientServerRepo.git

2. Set git http & https proxy:
	git config --global http.proxy http://nsn-intra.net\\<user>:<pass>@10.144.1.10:8080
	git config --global https.proxy http://nsn-intra.net\\<user>:<pass>@10.144.1.10:8080

3. Set git authentication file (in root of downloaded repo) .git/config, change line:
	url=https://github.com/USER/REPO to
	url=https://<gituser>:<gitpass>@github.com/USER/REPO

4. Enjoy pushing changes:
	git push

Git tutorial for dummies:

git add . - add current directory to local changes

git checkout master - make sure we're on master branch

git commit -m "Message" - commit locally with message "Message"

git push - push local commit to github
