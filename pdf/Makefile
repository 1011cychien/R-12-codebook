.PHONY: clean all

all: codebook.pdf

content.tex: content.yaml gen_content.py
	python3 gen_content.py

codebook.pdf: content.tex codebook.tex
	latexmk --xelatex --shell-escape codebook.tex

clean:
	$(RM) codebook.pdf content.tex
	latexmk --xelatex -c codebook.tex
