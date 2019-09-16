SUBDIRS = source
EXTRA_DIST = bideuchre.nsi Doxyfile apidocs docs/*.txt docs/*.html \
	vstudio\bideuchre.sln vstudio\bideuchre.vcxproj \
	vstudio\bideuchre.vcxproj.filters vstudio\bideuchre.vcxproj.user

.PHONY: allclean apidocs bundle touch

allclean: clean
	-rm -rf source/hack4u.app
	-rm -rf apidocs
	-rm -f *.bz2
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen

bundle:
	-cd source && make bideuchre.app

touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;
