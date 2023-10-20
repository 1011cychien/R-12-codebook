
docs.pdf: *.md
	sed 's/^#/\n#/g' \
		Basic.md DataStructure.md FlowAndMatching.md \
	       	Graph.md Math.md Geometry.md String.md Misc.md | \
	       	pandoc -f markdown -o docs.pdf --pdf-engine=xelatex --metadata-file meta.yaml
clean:
	rm docs.pdf -f

.PHONY: clean
