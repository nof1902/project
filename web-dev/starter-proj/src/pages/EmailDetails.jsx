import { useEffect, useState } from "react"
import { useNavigate, useParams } from "react-router-dom"
import { emailService } from '../services/email.service'
import imgUrlback from '/back.png'

export function EmailDetails(){

    const [email, setEmail] = useState(null);
    const params = useParams();
    const navigate = useNavigate();

    useEffect(() => {
        loadEmail()
    }, [params.id])

    async function loadEmail() {
        try {
            const email = await emailService.getById(params.id)
            setAsRead(email)
            setEmail(email)
        } catch (error) {
            console.log('error:', error)
        }
    }

    async function setAsRead(email){
        email.isRead = true;
        const new_email = await emailService.save(email)
        console.log(new_email)
    }

    function onBack() {
        navigate('/emails')
    }

    if (!email) return <div>Loading...</div>
    
    return(
        <section className="email-details">
            <section className="header-page">
                <h1>{email.subject}</h1>
                <section className="actions">
                    {/* <img src={imgUrlremove} alt="Remove message" onClick={() => onRemoveEmail(email.id) } /> */}
                    <img src={imgUrlback} alt="Back to Inbox" onClick={onBack} />
                </section>
            </section>
            <section className="body-page">
                <p className="body-of-email">{email.body}</p>
                <p className="email-data">this email sent from {'<' + email.from + '>'} at {email.sentAt} to {email.to}</p>
            </section>
        </section>
        
    )
}