import numpy as np

#Downloaded Functions
def generate_trainingdata(m=25):
    return np.array([0,0])+0.25*np.random.randn(m,2)

def f(x, minibatch):
    # loss function sum_{w in training data} f(x,w)
    y=0; count=0
    for w in minibatch:
        z=x-w-1
        y=y+min(31*(z[0]**2+z[1]**2), (z[0]+7)**2+(z[1]+5)**2)
        count=count+1
    return y/count



def mini_batch(data, batch_size):
    batches = []
    np.random.shuffle(data)
    n = len(data)
    for i in np.arange(0, n, batch_size):
        batch = data[i:(i + batch_size)] if i + batch_size < n else data[i:n]
        batches.append(batch)
    return batches


def batch_finite_diff(f, pt, batch, h=1e-8):
    batch_dx = (f([pt[0] + h, pt[1]], batch) - f(pt, batch))/h
    batch_dy = (f([pt[0], pt[1] + h], batch) - f(pt, batch))/h
    return batch_dx, batch_dy


def constant(f, starting_point, data, alpha, tol, max_iters=1000, batch_size=32):
    x, y = starting_point[0], starting_point[1]
    path=[(x, y)]
    f_vals=[]

    for _ in range(max_iters):
        for batch in mini_batch(data, batch_size=batch_size):
            dx, dy = batch_finite_diff(f, [x,y], batch, h=1e-8)
            x -= alpha * dx
            y -= alpha * dy

            path.append((x,y))
            f_vals.append(f([x, y], batch))

        if np.sqrt(dx**2 + dy**2) < tol:
            break

    return path, f_vals




def Polyak(f, starting_point, data, epsilon=1e-8, f_star=0, max_iters=1000, batch_size=32):
    x, y = starting_point[0], starting_point[1]
    path=[(x, y)]
    f_vals=[]

    for _ in range(max_iters):
        for batch in mini_batch(data, batch_size=batch_size):
            dx, dy = batch_finite_diff(f, [x,y], batch, h=1e-8)
            alpha = (f([x, y], batch) - f_star)/(dx**2 + dy**2 + epsilon)
            x -= alpha * dx
            y -= alpha * dy

            path.append((x,y))
            f_vals.append(f([x, y], batch))

    return path, f_vals

def RMSProp(f, starting_point, data, alpha0, beta, epsilon=1e-8, max_iters=1000, batch_size=32):
    x, y = starting_point[0], starting_point[1]
    sum_dx = 0
    sum_dy = 0
    path = [(x, y)]
    f_vals = []

    for t in range(1, max_iters + 1):
        for batch in mini_batch(data, batch_size=batch_size):
            # Take gradients for current x, y
            dx, dy = batch_finite_diff(f, [x,y], batch, h=1e-8)

            # Update denominator for x and y using the following
            sum_dx = beta * sum_dx + (1 - beta) * dx**2
            sum_dy = beta * sum_dy + (1 - beta) * dy**2

            # Compute the step sizes for x and y
            step_size_x = alpha0 / np.sqrt(sum_dx + epsilon)
            step_size_y = alpha0 / np.sqrt(sum_dy + epsilon)

            # Update x and y
            x -= step_size_x * dx
            y -= step_size_y * dy

            path.append((x, y))
            f_vals.append(f([x, y], batch))

    return path, f_vals

def heavy_ball(f, starting_point, data, alpha, beta, max_iters=1000, tol=1e-5, batch_size=32, stopping=True):
    # Initialize x,y, momentum variables and path,f(x,y) lists
    x, y = starting_point[0], starting_point[1]
    ux, uy = 0, 0
    path = [(x, y)] 
    f_vals = []
    
    for _ in range(max_iters):
        for batch in mini_batch(data, batch_size=batch_size):
            # Take gradients for current x, y
            dx, dy = batch_finite_diff(f, [x,y], batch, h=1e-8)
            
            # Update momentum variable with current and past momentum
            ux = beta * ux + alpha * dx
            uy = beta * uy + alpha * dy
            
            # Update x and y
            x -= ux
            y -= uy

            # Store the new values
            path.append((x, y))  
            f_vals.append(f([x, y], batch))

        if f([x, y], batch) > 1e10:
                break  
        # Check if the norm of the gradient is below the tolerance
        if np.sqrt(dx**2 + dy**2) < tol and stopping == True:
            break
        
    
    return path, f_vals



def adam(f, starting_point, data, alpha, beta1, beta2, epsilon=1e-6, max_iters=1000, tol=1e-5, batch_size=32,):
    # Initialize x,y, momentum variables and path,f(x,y) lists
    x, y = starting_point[0], starting_point[1]
    m_x, m_y = 0, 0
    v_x, v_y = 0, 0
    path = [(x, y)] 
    f_vals = []
    
    for t in range(1, max_iters + 1):
        for batch in mini_batch(data, batch_size=batch_size):
            # Take gradients for current x, y
            dx, dy = batch_finite_diff(f, [x,y], batch, h=1e-8)

            # Update momentum variable for gradient
            m_x = beta1 * m_x + (1 - beta1) * dx
            m_y = beta1 * m_y + (1 - beta1) * dy
            # Update momentum variable for squared gradient
            v_x = beta2 * v_x + (1 - beta2) * dx**2
            v_y = beta2 * v_y + (1 - beta2) * dy**2
            # Compute bias-corrected estimates
            m_x_hat = m_x / (1 - beta1**t)
            m_y_hat = m_y / (1 - beta1**t)

            v_x_hat = v_x / (1 - beta2**t)
            v_y_hat = v_y / (1 - beta2**t)

            # Update variables
            x -= alpha * m_x_hat / (np.sqrt(v_x_hat) + epsilon)
            y -= alpha * m_y_hat / (np.sqrt(v_y_hat) + epsilon)

            path.append((x, y)) 
            f_vals.append(f([x, y], batch))
        if f([x, y], batch) > 1e10:
                break
    
    return path, f_vals


def const_GD(f, starting_point, alpha, training_data, max_iters=1000, tol=1e-6):
    x, y = starting_point[0], starting_point[1]
    path=[(x, y)]
    f_vals=[]
    for _ in range(max_iters):
        dx, dy = batch_finite_diff(f, [x,y], training_data, h=1e-8)
        
        x -= alpha * dx
        y -= alpha * dy

        path.append((x,y))
        f_vals.append(f([x, y], training_data))


    return path, f_vals


def SGD(optimizer, f, starting_point, data, batch_size=32, max_iters=1000, **kwargs):
    optimizer = optimizer.strip().lower()
    if optimizer not in ['constant', 'polyak', 'rmsprop', 'hb', 'adam']:
        raise ValueError("Optimizer argument not valid")
    
    if optimizer == 'constant':
        alpha = kwargs.get('alpha', 0.01)
        tol = kwargs.get('tol', 1e-8)
        path, f_vals = constant(f=f, starting_point=starting_point, data=data, alpha=alpha, tol=tol, max_iters=max_iters, batch_size=batch_size)
        print("Stochastic-Gradient-Descent using Constant Optimiser")
        return path, f_vals

    elif optimizer == 'polyak':
        f_star = kwargs.get('f_star', 0.0)
        epsilon = kwargs.get('epsilon', 1e-8)

        path, f_vals = Polyak(f=f, starting_point=starting_point, data=data, f_star=f_star, epsilon=epsilon,  max_iters=max_iters, batch_size=batch_size)
        print("Stochastic-Gradient-Descent using Polyak Optimiser")
        return path, f_vals

    elif optimizer == 'rmsprop':
        alpha0 = kwargs.get('alpha0', 0.01)
        beta = kwargs.get('beta', 0.9)
        epsilon = kwargs.get('epsilon', 1e-8)

        path, f_vals = RMSProp(f=f, starting_point=starting_point, data=data, alpha0=alpha0, beta=beta,epsilon=epsilon,  max_iters=max_iters, batch_size=batch_size)
        print("Stochastic-Gradient-Descent using RMSProp Optimiser")
        return path, f_vals

    elif optimizer == 'hb':
        alpha = kwargs.get('alpha', 0.01)
        beta = kwargs.get('beta', 0.9)
        tol = kwargs.get('tol', 1e-5)

        path, f_vals = heavy_ball(f=f, starting_point=starting_point, data=data, alpha=alpha, beta=beta, max_iters=max_iters, tol=tol, batch_size=32)
        print("Stochastic-Gradient-Descent using Heavy-Ball Optimiser")
        return path, f_vals


    elif optimizer == 'adam':
        alpha = kwargs.get('alpha', 0.001)
        beta1 = kwargs.get('beta1', 0.9)
        beta2 = kwargs.get('beta2', 0.999)

        epsilon = kwargs.get('epsilon', 1e-8)
        tol = kwargs.get('tol', 1e-5)

        path, f_vals = adam(f=f, starting_point=starting_point, data=data, alpha=alpha, beta1=beta1, beta2=beta2, epsilon=epsilon, max_iters=max_iters, tol=tol, batch_size=32)
        print("Stochastic-Gradient-Descent using Adam Optimiser")
        return path, f_vals
