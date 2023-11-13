.PHONY: clean all

all: codebook.pdf content.html

content.html: content.yaml gen_content.py
	python3 gen_content.py content.yaml --html content.html

content.tex: content.yaml gen_content.py
	python3 gen_content.py content.yaml --tex content.tex

codebook.pdf: content.tex codebook.tex
	latexmk --xelatex --shell-escape codebook.tex

clean:
	$(RM) codebook.pdf content.tex content.html
	latexmk --xelatex -c codebook.tex || true
