import { useState } from "react"
import { Link } from "react-router-dom"
import imgUrlclose from '/close.png'
import imgUrlopen from '/open.png'
import imgUrlremove from '/remove.png'

export function EmailPreview({ email , onRemoveEmail}){

    const [isRead, setIsRead] = useState(false)
    const readModeClass = isRead ? 'read' : ''

    // use ref = the mail that read
    
    return (
        <Link to={`/emails/${email.id}`}>
            <article className={`email-preview ${readModeClass}`} onClick={() => { setIsRead(!isRead) }}>
                <section className="starred"></section>
                <h1 className="from">{email.from}</h1>
                <h1 className="subject">{email.subject}</h1>
                <h1 className="sent-at">{email.sentAt}</h1>
                <section className="IsRead">
                    { isRead ? (<img src={imgUrlopen} alt="Mark as read" onClick={() => { setIsRead(!isRead) }} />
                    ) : (
                        <img src={imgUrlclose} alt="Mark as unread" onClick={() => { setIsRead(!isRead) }} /> 
                        )}
                </section>
                <section className="remove-email">
                        <img src={imgUrlremove} alt="Remove message" onClick={() => onRemoveEmail(email.id)} />
                </section>
            </article>
        </Link>
    )
}




