#include <incl/domain/transformpayload.h>


QList<IODeviceDTO *> TransformPayload::transformPayloadToDtoIODeviceList(const QByteArray& byteArray) {
    int i = 0, j = 1;
    QString part = "";
    bool shouldConvert = false;
    auto * ioDeviceDto = new IODeviceDTO();
    QList<IODeviceDTO *> ioDeviceDTOList;

    for(QChar c: byteArray) {

        if(c.isSpace() || (j == byteArray.size())) {
            // hit EOL, add last part
            i = 0;
            // add last value and clear part
            ioDeviceDto->isLOW = part.toInt() == 1;
            part.clear();
            // add to list
            ioDeviceDTOList.append(ioDeviceDto);
            ioDeviceDto = new IODeviceDTO();
            //qInfo() << "hit space";
        }
        else if (c == ',') {
            //qInfo() << "hit splitter, set convert true";
            shouldConvert = true;
        }
        if (shouldConvert) {
            //qInfo() << "converted = " << part;
            switch (i) {
                case 0 :
                    ioDeviceDto->id = part.toInt();
                    break;
                case 1 :
                    ioDeviceDto->actionId = part.toInt();;
                    break;
                case 2 :
                    ioDeviceDto->typeId = part.toInt();;
                    break;
                default:
                    break;
            }
            i++;
            part.clear();
            shouldConvert = false;
        }
        if (c.isDigit()) {
            part.append(c);
            //qInfo() << "append to string";
        }
        j++;
    }
    return ioDeviceDTOList;
}
