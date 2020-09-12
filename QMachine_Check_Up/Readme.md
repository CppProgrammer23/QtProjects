#SQL #database #network
This project uses only phpMyAdmin (no sw is installed on my computer)

Since Qt doesn't provide a handle to MySql, you have to download the right binary which has to be compatible with your current Qt version @: https://github.com/thecodemonkey86/qt_mysql_driver/releases

Once done, create a new folder in your build project called sqldrivers (not in the first folder project which was generate after you create it), now copy the qsqlmysqld.dll (for debug) in the folder created (qsqlmysql.dll is for release). also you have to copy libmysql.dll in the folder where the excutable is (in build folder).
