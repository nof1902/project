import { EmailPreview } from "./EmailPreview";


export function EmailList({ emails, onRemoveEmail }) {
    return (
        <ul className="email-list">
            {emails.map(email => (
                <li key={email.id}>
                    <EmailPreview email={email} onRemoveEmail={onRemoveEmail}/>
                </li>

            ))}
        </ul>
    )
}