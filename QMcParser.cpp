#include "QMcParser.h"
#include <mcnet.h>
#include <QMap>
#include <QDebug>

QMap<mcnet_parser_t*, QMcParser*> QMcParser::parser2parser;

QMcParser::QMcParser(QObject *parent) :
    QObject(parent)
{
    parser = (mcnet_parser_t *)malloc(sizeof(mcnet_parser_t));
    parser->data = NULL;
    QMcParser::parser2parser.insert(parser, this);
    settings = (mcnet_parser_settings_t *)malloc(sizeof(mcnet_parser_settings_t));
    settings->on_packet = QMcParser::on_packet;
    settings->on_error = QMcParser::on_error;
    this->buffer = new QByteArray();
}

void QMcParser::start(QIODevice *input)
{
    this->input = input;
    connect(input, SIGNAL(readyRead()), this, SLOT(readData()));
}

void QMcParser::readData()
{
    QByteArray data = input->readAll();
    buffer->append(data);
    int parsed=0;
    while((parsed = mcnet_parser_execute(parser, settings, (uint8_t *)buffer->data(), buffer->size())) != 0) {
        buffer = new QByteArray(buffer->right(buffer->size() - parsed));
    }
}

void QMcParser::on_packet(mcnet_parser_t *parser, mcnet_packet_t *packet)
{
    if(QMcParser::parser2parser.contains(parser)) {
        QMcParser *p = QMcParser::parser2parser.value(parser);
        p->packet(packet);

    }
}

void QMcParser::on_error(mcnet_parser_t *parser, int err)
{
    if(QMcParser::parser2parser.contains(parser)) {
        QMcParser *p = QMcParser::parser2parser.value(parser);
        p->error(err);
    }
}

void QMcParser::packet(mcnet_packet_t *packet)
{
    // TODO: wrap the packets into something nice?
    this->onPacket(packet);
}

void QMcParser::error(int error)
{
    if(error != MCNET_EAGAIN) {
        this->onError(error);
    }
}
