all: build

lint: pjs.py pjscript
	pylint --disable=fixme --exit-zero pjs pjscript  # run pylint with rules

build: pjs.py pjscript setup.cfg
	rm -rf dist/*  # <---- do not forget to clean the ./dist directory first
	python -m build

upload: lint build
	python -m twine upload --repository pypi --verbose ./dist/tjscript-*.whl

install: lint build
	pip install --force-reinstall dist/tjscript-*.whl  # force reinstall pkg

runtime: runtime/cxx
	cd runtime/cxx && mkdir -p build && cd build && cmake .. && make && cd -

tests:
	@./test.sh examples/sample  # <---- run comparison test against 'sample'
	@./test.sh examples/simple  # <---- run comparison test against 'simple'

build-upload-install: lint build
	python -m twine upload --repository pypi --verbose ./dist/tjscript-*.whl
	pip install --force-reinstall dist/tjscript-*.whl  # force reinstall pkg