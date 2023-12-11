import { EmailPreview } from "./EmailPreview";
import 
import imgUrlremove from '/remove.png'

export function EmailList({ emails, onRemoveEmail }) {
    return (
        <ul className="email-list">
            {emails.map(email => (
                <li key={email.id}>
                    <EmailPreview email={email} onRemoveEmail={onRemoveEmail}/>
                    <EmailFilter />
                </li>
            ))}
        </ul>
    )
}