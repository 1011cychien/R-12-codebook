"""Convert content.yaml to content.tex + content.html"""

import argparse
import hashlib
import subprocess
from typing import List, Dict, Any, IO
from os import path
import yaml
from git import Repo


def md5hex(raw_s: str) -> str:
    """compute md5 hex string"""
    md5 = hashlib.md5()
    md5.update(raw_s.encode("utf8"))
    return md5.hexdigest()


def strip_whitespaces(raw_s: str) -> str:
    """works as `tr -d '[:space:]'`"""
    whitespaces = [" ", "\n", "\r", "\t", "\v"]
    return "".join(char for char in raw_s if char not in whitespaces)


def escape_latex(raw_s: str) -> str:
    """escape latex special characters"""
    escape_list = {
        "&": r"\&",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "_": r"\_",
    }
    return "".join(escape_list.get(char, char) for char in raw_s)


def gen_tex(sections: List[Dict[str, Any]], out: IO) -> None:
    """generate content.tex"""
    for section in sections:
        title = escape_latex(section["name"])
        prefix = section["prefix"]
        out.write("\\SectionTitle{%s}\n" % title)
        out.write("\\renewcommand\\Prefix{%s}\n" % prefix)
        for content in section["content"]:
            base, ext = path.splitext(content["path"])
            if ext == ".cpp":
                preprocessed = subprocess.check_output(
                    [
                        "cpp",
                        "-dD",
                        "-P",
                        "-fpreprocessed",
                        path.join(prefix, content["path"]),
                    ]
                ).decode("utf8")
                stripped = strip_whitespaces(preprocessed)
                cpp_hash = md5hex(stripped)[:6]
                out.write(
                    "\\IncludeCode[][%s]{%s}{%s}\n"
                    % (
                        " {\\small [%s]}" % cpp_hash,
                        escape_latex(content["name"]),
                        content["path"],
                    )
                )
            elif ext == ".tex":
                out.write(
                    "\\IncludeTex{%s}{%s}\n"
                    % (escape_latex(content["name"]), content["path"])
                )
            elif base == "vimrc":
                out.write(
                    "\\IncludeCode[language=vim]{%s}{%s}\n"
                    % (escape_latex(content["name"]), content["path"])
                )
            else:
                raise NotImplementedError(f"unsupported extension name: {ext}")


def gen_html(sections: List[Dict[str, Any]], out: IO) -> None:
    """generate content.html"""
    out.write(
        """<!doctype html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<meta charset="utf8">
<title>ckiseki codebook</title>
<style>
html, body, div, span, applet, object, iframe,
h1, h2, h3, h4, h5, h6, p, blockquote, pre,
a, abbr, acronym, address, big, cite, code,
del, dfn, em, img, ins, kbd, q, s, samp,
small, strike, strong, sub, sup, tt, var,
b, u, i, center,
dl, dt, dd, ol, ul, li,
fieldset, form, label, legend,
table, caption, tbody, tfoot, thead, tr, th, td,
article, aside, canvas, details, embed,
figure, figcaption, footer, header, hgroup,
menu, nav, output, ruby, section, summary,
time, mark, audio, video {
  margin: 0;
  padding: 0;
  border: 0;
  font-size: 100%;
  font: inherit;
  vertical-align: baseline;
}
body {
  line-height: 1;
}
ol, ul {
  list-style: none;
}
blockquote, q {
  quotes: none;
}
blockquote:before, blockquote:after,
q:before, q:after {
  content: '';
  content: none;
}
table {
  border-collapse: collapse;
  border-spacing: 0;
}
body {
  font-family: sans-serif;
}
h1 {
  font-size: 1.5rem;
  font-weight: 600;
}
h2 {
  font-size: 1.2rem;
  font-weight: 600;
  margin-top: 10px;
}
a {
  text-decoration: none;
  color: #375af0;
}
a:active {
  color: #375af0;
}
a:hover {
  text-decoration: underline;
}
.container {
  padding: 80px 10%;
}
li {
  margin-top: 5px;
}
</style>
</head>
<body>
<div class="container">
  <h1><a href="https://github.com/OmeletWithoutEgg/ckiseki">ckiseki</a></h1>
  <a href="https://github.com/OmeletWithoutEgg/ckiseki/raw/master/pdf/codebook.pdf">
    Latest content
  </a>
  <a href="https://github.com/OmeletWithoutEgg/ckiseki/raw/master/docs/docs.pdf">
    Latest document
  </a>
  <hr/>
"""
    )
    repo = Repo("..")
    root_path = path.realpath("..")
    for section in sections:
        prefix = section["prefix"]
        out.write(
            "<h2>"
            + "<a href='https://github.com/OmeletWithoutEgg"
            + f"/ckiseki/blob/master/docs/{section['doc']}'>"
            + section["name"]
            + "</a>"
            + "</h2>"
            + "<ul>"
        )
        for content in section["content"]:
            out.write("<li>")
            file_path = path.join(prefix, content["path"])
            real_path = path.realpath(file_path)
            commits = list(repo.iter_commits(max_count=1, paths=real_path))
            commit_hash = str(commits[0]) if len(commits) > 0 else None
            print(content["name"], commit_hash, content["verified"])
            if content["verified"] is None:
                out.write(b"\xe2\x9d\x8c".decode("utf8"))
            elif content["verified"] == "skip":
                out.write(b"\xf0\x9f\x93\x9d".decode("utf8"))
            elif (
                commit_hash is None or
                content["verified"] != commit_hash[:len(content["verified"])]
            ):
                out.write(b"\xe2\x9a\xa0\xef\xb8\x8f".decode("utf8"))
            else:
                out.write(b"\xe2\x9c\x85".decode("utf8"))
            out.write(
                " "
                + "<a href='https://github.com/OmeletWithoutEgg"
                + "/ckiseki/blob/master"
                + real_path[len(root_path):]
                + "'>"
                + content["name"]
                + "</a></li>"
            )
        out.write("</ul>")
    out.write("</div></body></html>")


def check_docs(sections: List[Dict[str, Any]], docs_dir: str):
    for section in sections:
        docs = section["doc"]

        names_in_doc = []
        with open(docs_dir + docs) as d:
            for line in d.readlines():
                line = line.strip()
                if line.startswith('## '):
                    names_in_doc.append(line[3:])

        names_in_yaml = []
        for content in section["content"]:
            names_in_yaml.append(content["name"])

        for name in names_in_yaml:
            if name not in names_in_doc:
                print(f'Section "{name}" is not documented.')
        for name in names_in_doc:
            if name not in names_in_yaml:
                print(f'Docs "{name}" is not in content.')
        import sys
        import difflib
        print('\n'.join(difflib.unified_diff(names_in_yaml, names_in_doc)))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate Contents")
    parser.add_argument(
        "content_yaml", type=argparse.FileType("r", encoding="utf8")
    )
    parser.add_argument("--tex", type=argparse.FileType("w", encoding="utf8"))
    parser.add_argument("--html", type=argparse.FileType("w", encoding="utf8"))
    args = parser.parse_args()
    sections_list = yaml.safe_load(args.content_yaml)
    if args.tex:
        gen_tex(sections_list, args.tex)
    if args.html:
        gen_html(sections_list, args.html)

    check_docs(sections_list, '../docs/')
