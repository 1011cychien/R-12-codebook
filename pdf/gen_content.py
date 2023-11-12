"""Convert content.yaml to content.tex"""

import hashlib
import subprocess
from os import path
import yaml


def md5hex(raw_s: str) -> str:
    """compute md5 hex string"""
    md5 = hashlib.md5()
    md5.update(raw_s.encode('utf8'))
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


if __name__ == "__main__":
    with open("content.yaml", "r", encoding="utf8") as content_yaml:
        sections = yaml.safe_load(content_yaml)
    with open("content.tex", "w", encoding="utf8") as out:
        for section in sections:
            title = escape_latex(section["name"])
            prefix = escape_latex(section["prefix"])
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
                        "\\IncludeCode[C++][%s]{%s}{%s}\n"
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
                        "\\IncludeCode[vim]{%s}{%s}\n"
                        % (escape_latex(content["name"]), content["path"])
                    )
                else:
                    raise NotImplementedError(f"unsupported extension name: {ext}")
