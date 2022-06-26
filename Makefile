all: build

lint: pjs.py pjscript
	pylint --exit-zero pjs pjscript  # do not want it to break build process

build: pjs.py pjscript setup.cfg
	rm -rf dist/*  # <---- do not forget to clean the ./dist directory first
	python -m build

upload: lint build
	python -m twine upload --repository pypi --verbose ./dist/pjscript-*.whl

install: lint build
	pip install --force-reinstall dist/pjscript-*.whl  # force reinstall pkg

runtime: runtime/cxx
	cd runtime/cxx && mkdir -p build && cd build && cmake .. && make && cd -

build-upload-install: lint build
	python -m twine upload --repository pypi --verbose ./dist/pjscript-*.whl
	pip install --force-reinstall dist/pjscript-*.whl  # force reinstall pkg