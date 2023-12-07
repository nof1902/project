import { Route, HashRouter as Router, Routes } from 'react-router-dom';

import { AppHeader } from './cmps/AppHeader'
import { AppFooter } from './cmps/AppFooter'
import { Home } from './pages/Home';
import { AboutUs } from './pages/AboutUs';
import { EmailIndex } from './pages/EmailIndex';

export function App() {

    return (
        <Router>
            <section className='main-app'>
                <AppHeader />
                <main className="container">
                    <Routes>
                        <Route path="/" element={<Home />} />
                        <Route path="/about" element={<AboutUs />}/>
                        <Route path="/email" element={<EmailIndex />} />
                    </Routes>
                </main>
                <AppFooter />
            </section>
        </Router>
    )
}

