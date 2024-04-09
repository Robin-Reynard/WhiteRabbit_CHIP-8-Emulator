#include <QtTest>

// add necessary includes here

class Test_WhiteRabbit : public QObject
{
    Q_OBJECT

public:
    Test_WhiteRabbit();
    ~Test_WhiteRabbit();

private slots:
    void test_case1();

};

Test_WhiteRabbit::Test_WhiteRabbit()
{

}

Test_WhiteRabbit::~Test_WhiteRabbit()
{

}

void Test_WhiteRabbit::test_case1()
{

}

QTEST_APPLESS_MAIN(Test_WhiteRabbit)

#include "tst_test_whiterabbit.moc"
