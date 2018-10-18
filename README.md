## Qt Process Manager: a rewrite using QTableView again

In master branch, Qt Quick is used.  qps originally has a widget-based implementation.
(The code could be cleaner though.)  The reason for this branch is not because
it's necessarily a way forward (because in this branch a lot of the old
features are omitted), but rather to show that after making a proper canonical
QAbstractTableModel subclass, it's possible to use it for both QTableView and
Qt Quick TableView interchangeably.

### Building

* Requires Qt 5.12 or newer
* qmake; make

### License

Qps is licensed under the terms of the
[GPLv2](http://choosealicense.com/licenses/gpl-2.0/) or any later version.


### Translation (Weblate)

<a href="https://weblate.lxqt.org/projects/lxqt/qps/">
<img src="https://weblate.lxqt.org/widgets/lxqt/-/qps/multi-auto.svg" alt="Translation status" />
</a>
