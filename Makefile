INSTDIR=/usr/local

mandelbrot:
	gcc src/mandelbrot.c -o mandelbrot.out
.PHONY: mandelbrot

clean:
	$(RM) mandelbrot.out
.PHONY: clean

install: mandelbrot
	test -d "${INSTDIR}/bin" || mkdir -p "${INSTDIR}/bin"
	cp -f mandelbrot.out "${INSTDIR}/bin/mandelbrot.out"
	cp -f mandelbrot "${INSTDIR}/bin/mandelbrot"
.PHONY: install

uninstall:
	$(RM) "${INSTDIR}/bin/mandelbrot.out"
	$(RM) "${INSTDIR}/bin/mandelbrot"
.PHONY: uninstall
