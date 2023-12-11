import imgUrl from '/gmaillogo.png'

export function AppHeader() {
    
    return (
        <header className="app-header">
            <img src={imgUrl} alt='gmail logo'></img>
            <h1>Gmail</h1>
        </header>
    )
}
