
import { NavLink } from "react-router-dom";

export function ToolBar() {
    return (
        <header className="app-toolbar">
            <section className="container">
                <section className="toolbar">
                    <nav>
                        <NavLink to="/">Home</NavLink>
                        <NavLink to="/about">About</NavLink>
                        <NavLink to="/emails">Inbox</NavLink>
                        {/* <NavLink to="/">Starred</NavLink>
                        <NavLink to="/">Draft</NavLink>
                    <NavLink to="/">Trash</NavLink> */}
                    </nav>
                </section>
            </section>
        </header>
    )
}
