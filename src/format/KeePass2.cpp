/*
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "KeePass2.h"
#include "crypto/kdf/AesKdf.h"
#include <QSharedPointer>


const Uuid KeePass2::CIPHER_AES = Uuid(QByteArray::fromHex("31c1f2e6bf714350be5805216afc5aff"));
const Uuid KeePass2::CIPHER_TWOFISH = Uuid(QByteArray::fromHex("ad68f29f576f4bb9a36ad47af965346c"));
const Uuid KeePass2::CIPHER_CHACHA20 = Uuid(QByteArray::fromHex("D6038A2B8B6F4CB5A524339A31DBB59A"));

const Uuid KeePass2::KDF_AES = Uuid(QByteArray::fromHex("C9D9F39A628A4460BF740D08C18A4FEA"));

const QByteArray KeePass2::INNER_STREAM_SALSA20_IV("\xE8\x30\x09\x4B\x97\x20\x5D\x2A");

const QList<QPair<Uuid, QString>> KeePass2::CIPHERS {
        qMakePair(KeePass2::CIPHER_AES, QObject::tr("AES: 256-bit")),
        qMakePair(KeePass2::CIPHER_TWOFISH, QObject::tr("Twofish: 256-bit")),
        qMakePair(KeePass2::CIPHER_CHACHA20, QObject::tr("ChaCha20: 256-bit"))
};
const QList<QPair<Uuid, QString>> KeePass2::KDFS {
        qMakePair(KeePass2::KDF_AES, QObject::tr("AES-KDF")),
};

QSharedPointer<Kdf> KeePass2::uuidToKdf(const Uuid& uuid)
{
    if (uuid == KDF_AES) {
        return QSharedPointer<AesKdf>::create();
    }

    Q_ASSERT_X(false, "uuidToKdf", "Invalid UUID");
    return nullptr;
}

KeePass2::ProtectedStreamAlgo KeePass2::idToProtectedStreamAlgo(quint32 id)
{
    switch (id) {
    case static_cast<quint32>(KeePass2::ArcFourVariant):
        return KeePass2::ArcFourVariant;
    case static_cast<quint32>(KeePass2::Salsa20):
        return KeePass2::Salsa20;
    case static_cast<quint32>(KeePass2::ChaCha20):
        return KeePass2::ChaCha20;
    default:
        return KeePass2::InvalidProtectedStreamAlgo;
    }
}
