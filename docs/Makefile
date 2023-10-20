docs.pdf: *.md
	printf -- "---\nscript:\n  - path: mathjax-config.js\n  - url: https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-chtml.js\n---\n" | cat - Basic.md DataStructure.md FlowAndMatching.md Graph.md Math.md Geometry.md String.md Misc.md | md-to-pdf --launch-options '{ "args": ["--no-sandbox", "--disable-setuid-sandbox"] }' > docs.pdf

clean:
	rm docs.pdf -f

.PHONY: clean
