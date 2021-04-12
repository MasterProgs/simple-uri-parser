# Simple-url-parser

Url-parser, such as : http(s), ftp, ssh, spotify, git

### Examples

```
https://www.google.fr/search?client=opera
ftp://user:mot-de-passe@mon-site.mondomaine/mon-repertoire/folder1/folder2/file.ext
ssh://user@host.xz:port/path/to/repo.git/
spotify:track:6xUy203RnyyOfbqf96Nven
http://username:password@www.my_site.com/hello/file.js
git://github.com/user/project-name.git
```

### Output

```
Trying to parse URL : ftp://user:mot-de-passe@mon-site.mondomaine/mon-repertoire/folder1/folder2/file.ext
protocol : `ftp`
domain = "mon-site.mondomaine"
username = "user"
password = "mot-de-passe"
path = "/mon-repertoire/folder1/folder2/file.ext"
```
