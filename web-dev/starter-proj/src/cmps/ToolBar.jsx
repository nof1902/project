
import { NavLink } from "react-router-dom";

export function ToolBar() {
    return (
        <section className="app-toolbar">
            <section className="compose-container">
                <button className='compose'>+Compose</button>
            </section>
            <section className="toolbar">
                <nav>
                    <NavLink to="/emails">Home</NavLink>
                    <NavLink to="/about">About</NavLink>
                    <NavLink to="/emails">Inbox</NavLink>
                    {/* <NavLink to="/">Starred</NavLink>
                    <NavLink to="/">Draft</NavLink>
                <NavLink to="/">Trash</NavLink> */}
                </nav>
            </section>
        </section>
    )
}
