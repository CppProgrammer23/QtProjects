# SQL | Database

This project uses only phpMyAdmin (no sw is installed on my computer)

Since Qt doesn't provide a handle to MySql, you have to download the right binary which has to be compatible with your current Qt version @: https://github.com/thecodemonkey86/qt_mysql_driver/releases

Once done, create a new folder in your build project called sqldrivers (not in the first folder project which was generate after you create it), now copy the qsqlmysqld.dll (for debug) in the folder created (qsqlmysql.dll is for release). also you have to copy libmysql.dll in the folder where the excutable is (in build folder).

Select MyISAM type to avoid "table is in read only mode" error
example of my saved values into db:
![ex_db](https://user-images.githubusercontent.com/62848804/92991884-833dbd80-f4de-11ea-88d4-410031d3ad83.png)


If you're using MinGw 32-bit it's better to add to _**..\mingw_32\plugins\sqldrivers**_, **qsqlmysql.dll** which works for both debug and release mode and also add **libmysql.dll** to your build folder inside the debug folder.

_**Enjoy**_
