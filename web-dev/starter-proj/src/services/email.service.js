import { storageService } from './async-storage.service.js'
import { utilService } from './util.service.js'

export const emailService = {
    query,
    save,
    remove,
    getById,
    createEmail,
}

const STORAGE_KEY = 'emails'

// localStorage.clear();
_createEmails()

async function query(filterBy) {
    const emails = await storageService.query(STORAGE_KEY)
    if (filterBy) {

    }
    return emails
}

function getById(id) {
    return storageService.get(STORAGE_KEY, id)
}

function remove(id) {
    return storageService.remove(STORAGE_KEY, id)
}

function save(emailToSave) {
    if (emailToSave.id) {
        return storageService.put(STORAGE_KEY, emailToSave)
    } else {
        emailToSave.isOn = false
        return storageService.post(STORAGE_KEY, emailToSave)
    }
}

function createEmail() {
    return {
            id: '',
            subject: '',
            body: '',
            isRead: false,
            isStarred: false,
            sentAt : 0,
            removedAt : null, //for later use
            from: '',
            to: ''
        }
}

function _createEmails() {
    let emails = utilService.loadFromStorage(STORAGE_KEY)
    if (!emails || !emails.length) {
        emails = [
            {
                id: 'e1', subject: 'Miss you!', body: 'Would love to catch up sometimes', isRead: false, isStarred: false,
                sentAt : 1551133930594, removedAt : null, from: 'momo@momo.com', to: 'user@appsus.com'
            },
            {
                id: 'e2', subject: 'Miss you!', body: 'Would love to catch up sometimes', isRead: false, isStarred: false,
                sentAt : 1551133930594, removedAt : null, from: 'momo@momo.com', to: 'user@appsus.com'
            },
            {
                id: 'e3', subject: 'Miss you!', body: 'Would love to catch up sometimes', isRead: false, isStarred: false,
                sentAt : 1551133930594, removedAt : null, from: 'momo@momo.com', to: 'user@appsus.com'
            }
        ]
        utilService.saveToStorage(STORAGE_KEY, emails)
    }
}


    




