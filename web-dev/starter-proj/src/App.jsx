import { Route, HashRouter as Router, Routes } from 'react-router-dom';

import { AppHeader } from './cmps/AppHeader'
import { AppFooter } from './cmps/AppFooter'
import { Home } from './pages/Home';
import { AboutUs } from './pages/AboutUs';
import { EmailIndex } from './pages/EmailIndex';
import { ToolBar } from './cmps/ToolBar';
import { EmailDetails } from './pages/EmailDetails';

export function App() {

    return (
        <Router>
            <section className='main-app'>
                <AppHeader />
                <ToolBar />
                <main className="container">
                    <Routes>
                        <Route path="/" element={<Home />} />
                        <Route path="/about" element={<AboutUs />}/>
                        <Route path="/emails" element={<EmailIndex />} />
                        <Route path="/emails/:id" element={<EmailDetails />} />
                    </Routes>
                </main>
                <AppFooter />
            </section>
        </Router>
    )
}

