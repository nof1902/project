
export function EmailFilter({  }) {
    return (
        <section className="email-filter">
            <form>
                <div className="text-filter">
                    <label htmlFor="txt">search word:</label>
                    <input name="txt" type="text" />
                </div>
                <div className="is-read-filter">    
                    <label htmlFor="is-read"> Is read</label>
                    <input name="is-read" type="checkbox" />
                </div>

            </form>
        </section>
    )
}