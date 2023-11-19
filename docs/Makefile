.PHONY: clean

docs.pdf: *.md
	sed 's/^#/\n#/g' \
		Basic.md DataStructure.md FlowAndMatching.md \
		Graph.md Math.md Geometry.md String.md Misc.md > docs.md
	pandoc -f markdown-smart \
		--toc \
		--pdf-engine=xelatex \
		--metadata-file meta.yaml \
		docs.md \
		-o docs.pdf
	rm docs.md

clean:
	rm docs.pdf -f
