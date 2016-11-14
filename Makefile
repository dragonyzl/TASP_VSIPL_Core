## Created RJudd
## SPAWARSYSCEN D881

all:
	(cd src_core; make;)
	(cd src_core_double; make;)
	(cd src_short_int; make;)
	(cd src_VU; make;)

development:
	(cd src_core; make development;)
	(cd src_core_double; make development;)
	(cd src_short_int; make development;)
	(cd src_VU; make;)

clean:
	(cd src_core; make clean;)
	(cd src_core_double; make clean;)
	(cd src_short_int; make clean;)
	(cd src_VU; make clean;)
