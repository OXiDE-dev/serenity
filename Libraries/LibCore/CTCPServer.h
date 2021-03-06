#pragma once

#include <AK/IPv4Address.h>
#include <LibCore/CNotifier.h>
#include <LibCore/CObject.h>

class CTCPSocket;

class CTCPServer : public CObject {
    C_OBJECT(CTCPServer)
public:
    virtual ~CTCPServer() override;

    bool is_listening() const { return m_listening; }
    bool listen(const IPv4Address& address, u16 port);

    RefPtr<CTCPSocket> accept();

    Optional<IPv4Address> local_address() const;
    Optional<u16> local_port() const;

    Function<void()> on_ready_to_accept;

private:
    explicit CTCPServer(CObject* parent = nullptr);

    int m_fd { -1 };
    bool m_listening { false };
    RefPtr<CNotifier> m_notifier;
};
