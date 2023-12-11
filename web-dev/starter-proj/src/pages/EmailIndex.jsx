import "../cmps/init"
import { useEffect, useState } from "react"
import { EmailList } from "../cmps/EmailList";
import { emailService } from '../services/email.service'
// import { EmailFilter } from "./EmailFilter"

export function EmailIndex() {
    
    const [emails, setEmails] = useState(null)
    // const [filterBy, setFilterBy] = useState(emailService.getDefaultFilter())

    useEffect(() => {
        loadEmail()
    },[])

    async function loadEmail() {
        const emails = await emailService.query()
        setEmails(emails)
    }

    async function onRemoveEmail(emailId) {
        try {
            await emailService.remove(emailId)
            setEmails(prevEmail => {
                return prevEmail.filter(email => email.id !== emailId)
            })
        } catch (error) {
            console.log('error:', error)
        }
    }

    if (!emails) return <div>Loading...</div>

    return (
        <section className=".email-details .container">
            {/* <EmailFilter /> */}
            <EmailList emails={emails} onRemoveEmail={onRemoveEmail} />
        </section>
    )
}
