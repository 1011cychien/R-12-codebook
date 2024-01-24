.PHONY: clean

docs.pdf: *.md meta.yaml
	sed 's/^#/\n#/g' \
		Basic.md DataStructure.md FlowAndMatching.md \
		Graph.md Math.md Geometry.md String.md Misc.md > docs.md
	pandoc -f markdown-smart \
		--toc \
		--toc-depth=2 \
		--pdf-engine=xelatex \
		--metadata-file meta.yaml \
		docs.md \
		-o docs.pdf
	rm docs.md

clean:
	rm docs.pdf -f
