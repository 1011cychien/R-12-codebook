FROM ubuntu:latest

ENV LANG C.UTF-8

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
  cpp \
  latexmk \
  texlive-lang-chinese \
  texlive-science \
  texlive-xetex \
  make \
  pandoc \
  git \
  python3 python3-pip \
  && rm -rf /var/lib/apt/lists/*

COPY pdf/requirements.txt requirements.txt
RUN pip install -r requirements.txt
## install git for auto-commit-action
