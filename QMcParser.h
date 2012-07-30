#ifndef QMCPARSER_H
#define QMCPARSER_H

#include <mcnet.h>
#include <QObject>
#include <QMap>
#include <QIODevice>

class QMcParser : public QObject
{
    Q_OBJECT
public:
    explicit QMcParser(QObject *parent = 0);
    static void on_packet(mcnet_parser_t* parser, mcnet_packet_t* packet);
    static void on_error(mcnet_parser_t* parser, int error);
    void start(QIODevice *input);
    static QMap<mcnet_parser_t*, QMcParser*> parser2parser;

protected:
    void packet(mcnet_packet_t* packet);
    void error(int error);
private:
    mcnet_parser_t *parser;
    mcnet_parser_settings_t *settings;
    QIODevice *input;
    QByteArray *buffer;
signals:
    onPacket(mcnet_packet_t* packet);
    onError(int error);
    
public slots:
    void readData();


};

#endif // QMCPARSER_H
